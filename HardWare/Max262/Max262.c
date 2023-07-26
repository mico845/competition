//
// Created by Whisky on 2023/3/31.
//
#include "Max262.h"
#include <math.h>

void write(u8 add,u8 dat2bit)
{
	u8 i;  
	if ((dat2bit & 0x01))
		HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, GPIO_PIN_RESET);
	if ((dat2bit & 0x10))
		HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, GPIO_PIN_RESET);
	if ((add & 0x0001))
		HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(A0_GPIO_Port, A0_Pin, GPIO_PIN_RESET);
	if ((add & 0x0010))
		HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(A1_GPIO_Port, A1_Pin, GPIO_PIN_RESET);
	if ((add & 0x0100))
		HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(A2_GPIO_Port, A2_Pin, GPIO_PIN_RESET);
	if ((add & 0x1000))
		HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(A3_GPIO_Port, A3_Pin, GPIO_PIN_RESET);
	resetWr;    
	for(i=0;i<255;i++);     //����250ns        
	setWr;   	
	for(i=0;i<100;i++);     //����10ns 
}



//����Aͨ��Fֵ     
void setAf(u8 datF)    //6λ����Ƶ��f0����λF0-F5 ��Ӧʮ����0-63
{    
	write(1,datF);         
	datF = datF>>2;         
	write(2,datF);         
	datF = datF>>2;         
	write(3,datF);    
}     
//����Aͨ��Qֵ     
void setAQ(u8 datQ)    //7λƷ������Q����λQ0-Q6 ��Ӧʮ����0-127
{    
	write(4,datQ);         
	datQ = datQ>>2;         
	write(5,datQ);         
	datQ = datQ>>2;         
	write(6,datQ);         
	datQ = (datQ>>2)&1;  //�Ե�ַ7ֻȡһλ         
	write(7,datQ);    
} 
//����Bͨ��Fֵ     
void setBf(u8 datF)    
{    
    write(9,datF);        
	datF = datF>>2;       
	write(10,datF);      
	datF = datF>>2;       
	write(11,datF);    
} 
    
//����Bͨ��Qֵ     
void setBQ(u8 datQ)    
{    
    write(12,datQ);         
	datQ = datQ>>2;        
	write(13,datQ);         
	datQ = datQ>>2;         
	write(14,datQ);    
    datQ = (datQ>>2)&1;
	write(15,datQ);    
}    
//***************************************************************     
//���ݽ�ֹƵ��fc��Ʒ������Q��ͨ��ģʽpassMode�����˲���������Ƶ��f0 
//�������ڵ�ͨ�͸�ͨ
//Q = 1 ʱ
//��ͨ��fc �� 1000-10000Hz ����500Hz  f0:769.23-7692.31Hz
//��ͨ��fc �� 1000-10000Hz ����500Hz  f0:1300-13000Hz
float lh_Getf0(float fc,float Q,u8 passMode) 
{    
    float temp; 
    temp = 1-0.5/pow(Q,2);   //pow(Q, 2) ����Q��2����
	temp = sqrt(temp+sqrt(pow(temp,2)+1));  
	if(passMode==lowPass)  //��ͨ����Ƶ�ʼ��㹫ʽ 
	{     
        return  fc/temp;          
	}      
	else  //��ͨ����Ƶ�ʼ��㹫ʽ       
	{ 
        return  fc*temp;  
	} 
}     
//����ʱ��Ƶ��fclk������Ƶ��f0���͹���ģʽworkMode��Ƶ���趨ֵFN     
//uchar getFn(float fclk,float f0,u8 workMode)    
//{ 
//       if (workMode==modeTwo)    
//       return (u8)(fclk*2.8284271247/f0/PI-26);       
//       else    
//       return (u8)(fclk*2/f0/PI-26);       
//}


//����fc��Q��passMode��workMode��ͨ��channel����MAX262�ĵ�ͨ�͸�ͨ�Ĺ������� 
//����ʱ��Ƶ��fclk 
//��ͨ��60384.6-603845.6Hz
//��ͨ��102050-1020500Hz
float lhp_WorkFclk(float fc,float Q,u8 passMode,u8 workMode,u8 channel)    
{       
	float f0;
	u8 Qn, Fn; 
	f0 = lh_Getf0(fc, Q, passMode);  
	if (workMode==modeTwo)
	{
		Qn = (u8)(128-90.51f/Q);
	}		
	else    
	{
		Qn = (u8)(128-64/Q);
	}		
	if(passMode==highPass)
	{        
		workMode=modeThree;  //��ֻͨ�й���ģʽ3  
	}
	
//	Fn = FnFin_config(f0, workMode);
	
   if(channel==channelA)       
	{ 
    write(0,workMode);         
		setAf(0);  //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setAQ(Qn);       
	}     
	else 
  { 
    write(8,workMode);         
		setBf(0);     //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setBQ(Qn);       
	}  
  if(workMode==modeTwo)
	{        
		return  28.87872f*f0;//(Fn+26)*1.11072f*f0;//31.46625f*PI*f0;//31.46625-63   16.26361-20
	}
	else
	{		
    return  40.84071f*f0;//(26+Fn)*PI/2*f0;//44.5*PI*f0;//44.5-63  23-20
	} 
}
//����fh��fl��workMode��ͨ��channel����MAX262�Ĵ�ͨ�������� 
//����ʱ��Ƶ��fclk 

float bp_WorkFclk(float fh,float fl,u8 workMode,u8 channel)    
{   
  float f0,Q;    
	u8 Qn, Fn; 
  f0 = sqrt(fh*fl);   
	Q = f0/(fh-fl); 
 
	if (workMode==modeTwo)
	{
          Qn = (u8)(128-90.51f/Q);       
	}
	else
	{		
          Qn = (u8)(128-64/Q); 
	}		
	
//	Fn = FnFin_config(f0, workMode);
	
	if(channel==channelA) 
	{
	write(0,workMode);         
	setAf(0);  //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ. 
	setAQ(Qn); 
	}     
	else       
	{ 
    write(8,workMode);         
		setBf(0);     //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setBQ(Qn);       
	}   
	if(workMode==modeTwo)
	{        
		return 28.87872f*f0;//(Fn+26)*1.11072f*f0;//31.46625*PI*f0;     
	}
	else
	{		
    return 40.84071f*f0;//(26+Fn)*PI/2*f0;//44.5*PI*f0; 
	}
}
//����f0��Q��workMode��ͨ��channel����MAX262���ݲ��������� 
//����ʱ��Ƶ��fclk 
float bs_WorkFclk(float f0,float Q,u8 workMode,u8 channel) 
{ 
	u8 Qn; 
    if (workMode==modeTwo)              
	{
		Qn = (u8)(128-90.51f/Q);          
	}
	else
	{		
    Qn = (u8)(128-64/Q); 
	}		
	if(channel==channelA)		
	{ 
        write(0,workMode);         
		setAf(63);  //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setAQ(Qn);       
	}     
	else      
	{ 
		write(8,workMode);         
		setBf(63);     //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setBQ(Qn);       
	}   
	if(workMode==modeTwo)        
	{
		return  31.46625*PI*f0;     
	}
	else
	{		
       return  44.5*PI*f0; 
	}
}
//����f0��Q��ͨ��channel����MAX262��ȫͨ�������� 
//����ʱ��Ƶ��fclk 
float ap_WorkFclk(float f0,float Q,u8 channel) 
{    
	u8 Qn; 
    Qn = (u8)(128-64/Q);   
  
	if(channel==channelA) 
   { 
        write(0,modeFour);         
		setAf(63);  //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setAQ(Qn);       
	}     
	else 
    { 
        write(8,modeFour);         
		setBf(63);     //Ҫ���ô�Χ�ɵ������ص��ݵĲ���Ƶ�ʲ���ȡ���ֵ.         
		setBQ(Qn);       
	}   
	return  44.5*PI*f0; 
}