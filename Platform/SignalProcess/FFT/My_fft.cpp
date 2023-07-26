//
// Created by Whisky on 2023/5/23.
//
#include "SignalProcessBase.h"

/*
*********************************************************************************************************
*	函 数 名: Int_FFT_TAB
*	功能说明: 正弦和余弦表
*	形    参: FFT点数
*	返 回 值: 无
*********************************************************************************************************
*/
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
float32_t   costab[MAX_FFT_N/2];
float32_t   sintab[MAX_FFT_N/2];
void InitTableFFT(uint32_t n)
{
    uint32_t i;

/* 正常使用下面获取cos和sin值 */
#if 1
    for (i = 0; i < n/2; i ++ )
    {
        sintab[ i ]=  sin( 2 * PI * i / MAX_FFT_N );
        costab[ i ]=  cos( 2 * PI * i / MAX_FFT_N );
    }

/* 打印出来是方便整理cos值和sin值数组，将其放到内部Flash，从而节省RAM */
#else
    printf("const float32_t sintab[%d] = {\r\n", n);
	for (i = 0; i < n/2; i ++ )
	{
 		sintab[ i ]=  sin( 2 * PI * i / MAX_FFT_N );
		printf("%.11ff,\r\n", sintab[ i ]);
	}
	printf("};\r\n");

	printf("const float32_t costab[%d] = {\r\n", n);
	for (i = 0; i < n/2; i ++ )
	{
 		sintab[ i ]=  cos( 2 * PI * i / MAX_FFT_N );
		printf("%.11ff,\r\n", sintab[ i ]);
	}
	printf("};\r\n");
#endif
}
#endif

/*
*********************************************************************************************************
*	函 数 名: cfft
*	功能说明: 对输入的复数组进行快速傅里叶变换（FFT）
*	形    参: *_ptr 复数结构体组的首地址指针struct型
*             FFT_N 表示点数
*	返 回 值: 无
*********************************************************************************************************
*/
void _cfft(struct compx *_ptr, uint32_t FFT_N )
{
    float32_t TempReal1, TempImag1, TempReal2, TempImag2;
    uint32_t k,i,j,z;
    uint32_t Butterfly_NoPerColumn;				    /* 每级蝶形的蝶形组数 */
    uint32_t Butterfly_NoOfGroup;					/* 蝶形组的第几组 */
    uint32_t Butterfly_NoPerGroup;					/* 蝶形组的第几个蝶形 */
    uint32_t ButterflyIndex1,ButterflyIndex2,P,J;
    uint32_t L;
    uint32_t M;

    z=FFT_N/2;                  					/* 变址运算，即把自然顺序变成倒位序，采用雷德算法 */

    for(i=0,j=0;i<FFT_N-1;i++)
    {
        /*
          如果i<j,即进行变址 i=j说明是它本身，i>j说明前面已经变换过了，不许再变化，注意这里一般是实数 有虚数部分 设置成结合体
        */
        if(i<j)
        {
            TempReal1  = _ptr[j].real;
            _ptr[j].real= _ptr[i].real;
            _ptr[i].real= TempReal1;
        }

        k=z;                    				  /*求j的下一个倒位序 */

        while(k<=j)               				  /* 如果k<=j,表示j的最高位为1 */
        {
            j=j-k;                 				  /* 把最高位变成0 */
            k=k/2;                 				  /* k/2，比较次高位，依次类推，逐个比较，直到某个位为0，通过下面那句j=j+k使其变为1 */
        }

        j=j+k;                   				  /* 求下一个反序号，如果是0，则把0改为1 */
    }

    /* 第L级蝶形(M)第Butterfly_NoOfGroup组(Butterfly_NoPerColumn)第J个蝶形(Butterfly_NoPerGroup)****** */
    /* 蝶形的组数以2的倍数递减Butterfly_NoPerColumn，每组中蝶形的个数以2的倍数递增Butterfly_NoPerGroup */
    /* 在计算蝶形时，每L列的蝶形组数,一共有M列，每组蝶形中蝶形的个数,蝶形的阶数(0,1,2.....M-1) */
    Butterfly_NoPerColumn = FFT_N;
    Butterfly_NoPerGroup = 1;
    M = (uint32_t)log2(FFT_N);
    for ( L = 0;L < M; L++ )
    {
        Butterfly_NoPerColumn >>= 1;		/* 蝶形组数 假如N=8，则(4,2,1) */

        /* 第L级蝶形 第Butterfly_NoOfGroup组	（0,1，....Butterfly_NoOfGroup-1）*/
        for ( Butterfly_NoOfGroup = 0;Butterfly_NoOfGroup < Butterfly_NoPerColumn;Butterfly_NoOfGroup++ )
        {
            for ( J = 0;J < Butterfly_NoPerGroup;J ++ )	    /* 第 Butterfly_NoOfGroup 组中的第J个 */
            {					   						    /* 第 ButterflyIndex1 和第 ButterflyIndex2 个元素作蝶形运算,WNC */
                ButterflyIndex1 = ( ( Butterfly_NoOfGroup * Butterfly_NoPerGroup ) << 1 ) + J;/* (0,2,4,6)(0,1,4,5)(0,1,2,3) */
                ButterflyIndex2 = ButterflyIndex1 + Butterfly_NoPerGroup;/* 两个要做蝶形运算的数相距Butterfly_NoPerGroup (ge=1,2,4) */
                P = J * Butterfly_NoPerColumn;				/* 这里相当于P=J*2^(M-L),做了一个换算下标都是N (0,0,0,0)(0,2,0,2)(0,1,2,3) */

                /* 计算和转换因子乘积 */
                TempReal2 = _ptr[ButterflyIndex2].real * costab[ P ] +  _ptr[ButterflyIndex2].imag * sintab[ P ];
                TempImag2 = _ptr[ButterflyIndex2].imag * costab[ P ] -  _ptr[ButterflyIndex2].real * sintab[ P ] ;
                TempReal1 = _ptr[ButterflyIndex1].real;
                TempImag1 = _ptr[ButterflyIndex1].imag;

                /* 蝶形运算 */
                _ptr[ButterflyIndex1].real = TempReal1 + TempReal2;
                _ptr[ButterflyIndex1].imag = TempImag1 + TempImag2;
                _ptr[ButterflyIndex2].real = TempReal1 - TempReal2;
                _ptr[ButterflyIndex2].imag = TempImag1 - TempImag2;
            }
        }

        Butterfly_NoPerGroup<<=1;							/* 一组中蝶形的个数(1,2,4) */
    }
}



void cfft_arm(float32_t *input, u32 fftSize, u8 ifftFlag, u8 bitReverseFlag, float32_t *fft_output_maxval)
{
    /* input 处理*/
    float32_t fft_input[fftSize * 2];

    for(u32 i = 0; i < fftSize; i++)
    {
        fft_input[i * 2] = input[i];
        fft_input[i * 2 + 1] = 0;
    }

    if (fftSize == 2048)
        arm_cfft_f32(&arm_cfft_sR_f32_len2048, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 1024)
        arm_cfft_f32(&arm_cfft_sR_f32_len1024, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 512)
        arm_cfft_f32(&arm_cfft_sR_f32_len512, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 4096)
        arm_cfft_f32(&arm_cfft_sR_f32_len4096, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 256)
        arm_cfft_f32(&arm_cfft_sR_f32_len256, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 128)
        arm_cfft_f32(&arm_cfft_sR_f32_len128, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 64)
        arm_cfft_f32(&arm_cfft_sR_f32_len64, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 32)
        arm_cfft_f32(&arm_cfft_sR_f32_len32, fft_input, ifftFlag, bitReverseFlag);
    else if (fftSize == 16)
        arm_cfft_f32(&arm_cfft_sR_f32_len16, fft_input, ifftFlag, bitReverseFlag);
    else
    {
        printf("error : fft_size set error\r\n");
        return;
    }
    arm_cmplx_mag_f32(fft_input, fft_output_maxval, fftSize);
}

void cfft_f32_mag(float32_t *buffer)
{
    uint32_t i;
    struct  compx s[MAX_FFT_N];

    /* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
    InitTableFFT(MAX_FFT_N);
#endif

    for(i=0; i<MAX_FFT_N; i++)
    {
        s[i].real = buffer[i];
        s[i].imag = 0;
    }

    /* MAX_FFT_N点快速FFT */
    _cfft(s, MAX_FFT_N);

    /* 计算幅频 */
    for(i=0; i<MAX_FFT_N; i++)
    {
        arm_sqrt_f32((float32_t)(s[i].real *s[i].real+ s[i].imag*s[i].imag ), &s[i].real);
        buffer[i] = s[i].real;
    }
}

SignalProcessBase& SignalProcessBase::fft_arm() {
    cfft_arm(signal, sample_num, 0, 1, signal);
#ifdef FFT_DEBUG
    debug();
#endif
    return *this;
}

SignalProcessBase& SignalProcessBase::ifft_arm() {
    cfft_arm(signal, sample_num, 1, 1, signal);
#ifdef FFT_DEBUG
    debug();
#endif
    return *this;
}

SignalProcessBase& SignalProcessBase::fft_mag() {
    cfft_f32_mag(signal);
#ifdef FFT_DEBUG
    debug();
#endif
    return *this;
}

void PowerPhaseRadians_f32(struct  compx *s, uint16_t _usFFTPoints, float32_t _uiCmpValue)
{
    float32_t lX, lY;
    uint32_t i;
    float32_t phase;
    float32_t mag;


    for (i=0; i <_usFFTPoints; i++)
    {
        lX= s[i].real; 	  /* 实部 */
        lY= s[i].imag;    /* 虚部 */

        phase = atan2f(lY, lX);    		  				 /* atan2求解的结果范围是(-pi, pi], 弧度制 */
        arm_sqrt_f32((float32_t)(lX*lX+ lY*lY), &mag);   /* 求模 */

        if(_uiCmpValue > mag)
        {
            s[i].real = 0;
        }
        else
        {
            s[i].real= phase * 180.0f/3.1415926f;   /* 将求解的结果由弧度转换为角度 */
        }
    }
}

void cfft_f32_phase(float32_t *buffer)
{
    uint32_t i;
    struct  compx s[MAX_FFT_N];
    /* 计算一批sin，cos系数 */
#if (MAX_FFT_N != 8192) && (MAX_FFT_N != 16384)
    InitTableFFT(MAX_FFT_N);
#endif

    for(i=0; i<MAX_FFT_N; i++)
    {
        s[i].real = buffer[i];
        s[i].imag = 0;
    }

    /* MAX_FFT_N点快速FFT */
    _cfft(s, MAX_FFT_N);

    /* 求相频 */
    PowerPhaseRadians_f32( s, MAX_FFT_N, 0.5f);

    for(i=0; i<MAX_FFT_N; i++)
    {
        buffer[i] = s[i].real;
    }
}

SignalProcessBase &SignalProcessBase::fft_phase() {
    cfft_f32_phase(signal);
    return *this;
}

