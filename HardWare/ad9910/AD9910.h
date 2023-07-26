#ifndef __AD9910_H__
#define __AD9910_H__

#include "main.h"
#include "delay.h"

#define uchar unsigned char
#define uint  unsigned int	
#define ulong  unsigned long int

#define AD9910_PWR              PBout(2)
#define AD9910_SDIO             PCout(2)
#define AD9910_DRHOLD           PDout(13)
#define AD9910_DROVER           PCout(3)
#define AD9910_UP_DAT           PAout(3)
#define AD9910_PROFILE1         PBout(0)
#define AD9910_MAS_REST         PBout(1)
#define AD9910_SCLK             PDout(14)
#define AD9910_DRCTL            PCout(0)
#define OSK                     PDout(10)
#define AD9910_PROFILE0         PAout(7)
#define AD9910_PROFILE2         PCout(5)
#define AD9910_CS               PCout(1)

typedef enum {
	TRIG_WAVE_1024 = 0,
	SQUARE_WAVE_1024,
	SINC_WAVE_1024,
    ARBITRARY_WAVE
} AD9910_WAVE_ENUM;

void AD9110_IOInit(void);
void Init_AD9910(void);
void AD9910_FreWrite(ulong Freq);										
void AD9910_AmpWrite(uint16_t Amp);
void AD9910_PhaseWrite(uint16_t Phase);

//Freq:   3.7Hz - 244K Hz   步进：3.72
void AD9910_RAM_WAVE_Set(AD9910_WAVE_ENUM wave, ulong Freq, uint16_t samples, const uint32_t *buffer);

void AD9910_DRG_AMP_Init(void);
void AD9910_DRG_FreInit_AutoSet(FunctionalState autoSweepEn);
void AD9910_DRG_FrePara_Set(u32 lowFre, u32 upFre, u32 posStep, u32 negStep, u16 posRate, u16 negRate);



#endif


