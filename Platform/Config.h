//
// Created by Whisky on 2023/5/24.
//

#ifndef HELLOWORLD_CONFIG_H
#define HELLOWORLD_CONFIG_H
/**********************************/
//DEBUG
/**********************************/
//#define TIM_DEBUG
//#define FFT_DEBUG
//#define ADC_DEBUG
//#define FILTER_DEBUG
//#define PWM_DEBUG
//#define WINDOWS_DEBUG
//#define RECGNIZE_DEBUG

/**********************************/
//ADC
/**********************************/
#define ADC_BUFF_SIZE (4096)

/**********************************/
//DAC
/**********************************/
#define DAC_BUFF_SIZE_MAX (4096)
#define DAC_BUFF_SIZE 10
#define MAX_VOL 3300

/**********************************/
//SIGNAL_PROCESS
/**********************************/
#define SIGNAL_BUFF_SIZE (ADC_BUFF_SIZE)

/**********************************/
//FILTER
/**********************************/
#define FILTER_LENGTH_SAMPLES   SIGNAL_BUFF_SIZE

/**********************************/
//PWM MEASURE
/**********************************/
//#define ENABLE_PWMMEASURE


/**********************************/
//SPWM
/**********************************/
#define SPWM_BUFF_SIZE_MAX (4096)
#define ENABLE_SPWM


/**********************************/
//FFT
/**********************************/
#define   MAX_FFT_N		 (SIGNAL_BUFF_SIZE)

#endif //HELLOWORLD_CONFIG_H
