
#include "PLL.h"
#include "math.h"
#include "stdint.h"

static _PLL_state value;


_PLL_state  GetPLLNum(void)
{
	return value;
}

void PLL_Data_Init(_PLL_state val)
{
	value = val;
	value.CHDIV1_MAX = 7;
	value.CHDIV1_MIN = 4;
	value.CHDIV2_MAX = 64;
	value.CHDIV2_MIN = 1;
	value.N_Divier_MAX = (u32)1<< value.N_Divier_BIT;
	value.DEN_Divier_MAX = (u32)1 << value.DEN_Divier_BIT;
	value.NUM_Divier_MAX = (u32)1 << value.NUM_Divier_BIT;
	value.PRE_R_Divier_MAX = (u32)1 << value.PRE_R_Divier_BIT;
	value.POST_R_Divier_MAX = (u32)1 << value.POST_R_Divier_BIT;

	value.MULT_MAX = 13;
	

}

/*�����������������Լ��--շת������ǵݹ�ʵ��*/
int greatCommonDivisor(int num1, int num2)
{
	while (num1*num2 != 0)
	{
		if (num1>num2)
			num1 %= num2;
		else
			num2 %= num1;
	}
	return (num1 == 0 ? num2 : num1);
}

u8 PLL_Calulate(u64 fre)
{
	u16 CHDIV1num, CHDIV2num,MULT,PRE_R,POST_R,R,ReR,ReMULT;

	u32 Fpd,N,pre,NUM,DEN;
	u64 Fvco;
	u32 val;
	u32 i=1,j;
	
	u64 FpdErr=-1;
	
	CHDIV1num = value.CHDIV1_MAX;
	CHDIV2num = value.CHDIV2_MAX;//����������ķ�Ƶ��ֵΪ���

	while(1)
	{

		pre = 2;
		PRE_R = 1;
		POST_R = 1;
		DEN = 80000;
		MULT = 1;
		//�����Ƶ���󳬳�VCOƵ�ʾͼ�����
		Fvco = fre*CHDIV1num*CHDIV2num;
		while (Fvco<value.min_VCO_freq || Fvco>value.max_VCO_freq)
		{
			if (CHDIV1num > value.CHDIV1_MIN)CHDIV1num--;
			else if (CHDIV2num > value.CHDIV2_MIN) { CHDIV2num /= 2; CHDIV1num= value.CHDIV1_MAX; }
			else return -1;
			Fvco = fre*CHDIV1num*CHDIV2num;
		}

		//��֤����Ƶ���ڹ涨��Χ��
//		Fpd = value.fpd*CHDIV1num*CHDIV2num / (1 << value.Prescalar_BIT);
//		if (Fpd < value.min_fpfd_freq)Fpd = value.min_fpfd_freq;
//		else if (Fpd > value.max_fpfd_freq) Fpd = value.max_fpfd_freq;

		Fpd = value.fpd;
		if (Fpd < value.min_fpfd_freq)Fpd = value.min_fpfd_freq;
		else if (Fpd > value.max_fpfd_freq) Fpd = value.max_fpfd_freq;
		
		//ͨ������Ƶ�����R���õ���ʵ����Ƶ��
		if (Fpd > value.clkin) i = Fpd / value.clkin + 1;

		for(;i<=value.MULT_MAX;i++)
		{
			for(j=1;j<=(u32)value.POST_R_Divier_MAX*value.PRE_R_Divier_MAX;j++)
			{
				if(Fpd>=value.clkin*i/j && FpdErr > (Fpd  - value.clkin*i/j))
				{
					FpdErr = Fpd  - value.clkin*i/j;
					ReR = j;
					ReMULT = i;
				}else if(Fpd<value.clkin*i/j && FpdErr > (value.clkin*i/j - Fpd))
				{
					FpdErr = value.clkin*i/j - Fpd;
					ReR = j;
					ReMULT = i;
				}
				if(FpdErr == 0)break;
			}
			if(FpdErr == 0)break;
		}
		
		if(value.PRE_R_Divier_MAX < ReR)
		{
			PRE_R = value.PRE_R_Divier_MAX;
			POST_R = ReR - value.PRE_R_Divier_MAX;
			MULT = ReMULT;
		}else
		{
			PRE_R = ReR;
			POST_R = 1;
			MULT = ReMULT;
		}
		
//		while (((Fpd % 100) > ((value.clkin*MULT / (PRE_R * POST_R)) % 100)))
//		{
//			if (PRE_R < value.PRE_R_Divier_MAX)PRE_R++;
//			else if (POST_R < MULT) { POST_R++; PRE_R = 1; }
//			else break;
//		}
		Fpd = (value.clkin*MULT / (PRE_R * POST_R));


		//����N��Ƶֵ
		N = Fvco / (Fpd*pre);
		if (N > value.N_Divier_MAX)
		{
			pre = 4;
			N = Fvco / (Fpd*pre);
			if (N > value.N_Divier_MAX)
			{
				if (CHDIV2num > 1)CHDIV2num /= 2;
				else if (CHDIV1num > 4)CHDIV1num--;
				else return -1;
				continue;
			}
		}
		NUM = Fvco*DEN / (Fpd*pre) - N*DEN;
		val = greatCommonDivisor(NUM, DEN);
		NUM /= val;
		DEN /= val;
		break;
	}
	value.PLL.nowfpd = Fpd;
	value.PLL.N_Divier = N;
	value.PLL.NUM_Divier = NUM;
	value.PLL.DEN_Divier = DEN;
	value.PLL.PRE_R_Divier = PRE_R;
	value.PLL.POST_R_Divier = POST_R;
	value.PLL.CHDIV1 = CHDIV1num;
	for (i = 0; CHDIV2num != 0; i++)
	{
		CHDIV2num /= 2;
	}
	value.PLL.CHDIV2 = i-1;
	value.PLL.Prescalar = pre;
	value.PLL.MULT = MULT;
	return 0;
}

