//
// Created by Whisky on 2023/7/17.
//

#ifndef HELLOWORLD_SPWM_H
#define HELLOWORLD_SPWM_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/
#include "arm_math.h"
#ifdef __cplusplus
}
/*---------------------------- C++ Scope ---------------------------*/
#ifdef ENABLE_SPWM
    void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif

#include "My_Dac.h"

class My_Spwm: public SignalPeripheral{
public:
    My_Spwm(TIM_HandleTypeDef* htim, uint8_t channel = TIM_CHANNEL_1) :
            SignalPeripheral(htim) , _channel(channel){ }
    ~My_Spwm() = default;
    My_Spwm& init(uint64_t f_out, uint64_t f_in, Waveform_Type wave, uint32_t samples);
    void start() override;
    void stop() override;
    My_Spwm& set_freq(uint32_t freq);
    My_Spwm& set_buffer(uint32_t *signal, uint32_t n, uint32_t samples);
    void calc_tim_arr_psc() override;
private:
    uint8_t _channel = TIM_CHANNEL_1;
    uint32_t _arr_length;
    uint32_t _samples;   //输出信号点数
    uint32_t _signal[SPWM_BUFF_SIZE_MAX];
    Waveform_Type _wave;
    friend void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
};

uint32_t *generateSinWave(uint32_t *buffer, uint32_t n, uint32_t maxval);
uint32_t *generateTriangleWave(uint32_t *buffer, uint32_t n, uint32_t maxval);


#endif
#endif //HELLOWORLD_SPWM_H
