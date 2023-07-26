//
// Created by Whisky on 2023/7/17.
//

#include "My_Spwm.h"
#include "retarget.h"

My_Spwm* spwm_instance1;
TIM_HandleTypeDef *__spwm_htim;

void My_Spwm::start() {
    calc_tim_arr_psc();
    if (_wave == Waveform_Triangle)
        generateTriangleWave(_signal, _samples, _arr_length);
    else if(_wave == Waveform_Sine)
        generateSinWave(_signal, _samples, _arr_length);
    HAL_TIM_Base_Start_IT(_htim);
    HAL_TIM_PWM_Start(_htim,_channel);
}

void My_Spwm::stop() {
    HAL_TIM_PWM_Stop(_htim, _channel);
}

My_Spwm& My_Spwm::set_freq(uint32_t freq) {
    _f_out = freq;
    calc_tim_arr_psc();
    return *this;
}

void My_Spwm::calc_tim_arr_psc()
{
    _htim->Instance->PSC = 1-1;
    float32_t arr = _f_in / (float32_t)_samples / (float32_t)_f_out ;
    while ((uint32_t)round(arr) >= UINT32_MAX)
    {
        arr /= 2;
        _samples *= 2;
    }
    _htim->Instance->ARR = (uint32_t)round(arr);
    _arr_length = _htim->Instance->ARR;
}

My_Spwm &My_Spwm::init(uint64_t f_out, uint64_t f_in, Waveform_Type wave, uint32_t samples) {
    _f_out = f_out;
    _f_in = f_in;
    __spwm_htim = _htim;
    _samples = samples;
    _wave = wave;
    spwm_instance1 = this;
    return *this;
}

My_Spwm &My_Spwm::set_buffer(uint32_t *signal, uint32_t n, uint32_t samples) {

    return *this;
}

uint32_t *generateSinWave(uint32_t *buffer, uint32_t n, uint32_t maxval) {
    const double pi = 3.14159265358979323846;
    for(uint32_t i = 0; i < n; i++) {
        double ratio = static_cast<double>(i) / static_cast<double>(n);
        double value = sin(2.0 * pi * ratio);
        buffer[i] = static_cast<uint32_t>((value + 1.0) / 2.0 * maxval);
    }
    return buffer;
}


uint32_t *generateTriangleWave(uint32_t *buffer, uint32_t n, uint32_t maxval) {
    float k = maxval / n * 2;
    float y = 0;
    for(uint32_t i = 0; i < n/2; i++) {
        y = k * i + 0;
        buffer[i] = (uint32_t)y;
    }

    for(uint32_t i = n/2; i < n; i++) {
        y = -k * i + k * n;
        buffer[i] = (uint32_t)y;
    }
    return buffer;
}

#ifdef ENABLE_SPWM
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == __spwm_htim->Instance)
    {
        static uint32_t i = 0;
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, spwm_instance1->_signal[i]);
        ++i;
        if (i >= spwm_instance1->_samples)
            i = 0;
    }
}
#endif


