/*
 * ad8934.h
 *
 *  Created on: Nov 6, 2022
 *      Author: Whisky
 */

#ifndef INC_AD9834_H_
#define INC_AD9834_H_


/********************************************************/
/* include                                              */
/********************************************************/
#include "main.h"

/********************************************************/
/* AD9834                                               */
/********************************************************/

/*引脚定义*/
//FSYNC D0
#define AD9834_FSYNC_Pin GPIO_PIN_0
#define AD9834_FSYNC_GPIO_Port GPIOD
//SCLK D1
#define AD9834_SCLK_Pin GPIO_PIN_1
#define AD9834_SCLK_GPIO_Port GPIOD
//SDATA D2
#define AD9834_SDATA_Pin GPIO_PIN_2
#define AD9834_SDATA_GPIO_Port GPIOD
//RESET D3
#define AD9834_RESET_Pin GPIO_PIN_3
#define AD9834_RESET_GPIO_Port GPIOD
//FS D4
#define AD9834_FS_Pin GPIO_PIN_4
#define AD9834_FS_GPIO_Port GPIOD
//PS D5
#define AD9834_PS_Pin GPIO_PIN_5
#define AD9834_PS_GPIO_Port GPIOD

#define AD9834_Control_Port GPIOD
#define AD9834_Fuction_Port GPIOD

#define Port_CLK_ON() {__HAL_RCC_GPIOC_CLK_ENABLE();}

/*引脚操作*/
//FSYNC
#define AD9834_FSYNC_SET	HAL_GPIO_WritePin(AD9834_FSYNC_GPIO_Port, AD9834_FSYNC_Pin, GPIO_PIN_SET)
#define AD9834_FSYNC_RESET	HAL_GPIO_WritePin(AD9834_FSYNC_GPIO_Port, AD9834_FSYNC_Pin, GPIO_PIN_RESET)
//SCLK
#define AD9834_SCLK_SET	HAL_GPIO_WritePin(AD9834_SCLK_GPIO_Port, AD9834_SCLK_Pin, GPIO_PIN_SET)
#define AD9834_SCLK_RESET	HAL_GPIO_WritePin(AD9834_SCLK_GPIO_Port, AD9834_SCLK_Pin, GPIO_PIN_RESET)
//SDATA
#define AD9834_SDATA_SET	HAL_GPIO_WritePin(AD9834_SDATA_GPIO_Port, AD9834_SDATA_Pin, GPIO_PIN_SET)
#define AD9834_SDATA_RESET	HAL_GPIO_WritePin(AD9834_SDATA_GPIO_Port, AD9834_SDATA_Pin, GPIO_PIN_RESET)
//RESET
#define AD9834_RESET_SET	HAL_GPIO_WritePin(AD9834_RESET_GPIO_Port, AD9834_RESET_Pin, GPIO_PIN_SET)
#define AD9834_RESET_RESET	HAL_GPIO_WritePin(AD9834_RESET_GPIO_Port, AD9834_RESET_Pin, GPIO_PIN_RESET)
//PS
#define AD9834_PS_SET	HAL_GPIO_WritePin(AD9834_PS_GPIO_Port, AD9834_PS_Pin, GPIO_PIN_SET)
#define AD9834_PS_RESET	HAL_GPIO_WritePin(AD9834_PS_GPIO_Port, AD9834_PS_Pin, GPIO_PIN_RESET)
//FS
#define AD9834_FS_SET	HAL_GPIO_WritePin(AD9834_FS_GPIO_Port, AD9834_FS_Pin, GPIO_PIN_SET)
#define AD9834_FS_RESET	HAL_GPIO_WritePin(AD9834_FS_GPIO_Port, AD9834_FS_Pin, GPIO_PIN_RESET)

//AD9834 MCLK周期
#define AD9834_MCLK (75000000UL)

/*频率寄存器*/
#define FREQ_0      0
#define FREQ_1      1

/*DB寄存器配置*/
//RESET
#define AD9834_RESET 0x2100

//Wave
#define Triangle_Wave       0x2002
#define Sine_Wave           0x2008
#define Square_Wave         0x2028

/********************************************************/
/* Function                                             */
/********************************************************/

void AD9834_WriteBytes(uint16_t data);

void AD9834_Init(void);

void AD9834_SetFreq(uint8_t, uint32_t);

void AD9834_SetWave(uint16_t initdata);

#endif /* INC_AD9834_H_ */
