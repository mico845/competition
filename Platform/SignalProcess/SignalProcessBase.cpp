//
// Created by Whisky on 2023/5/23.
//

#include "SignalProcessBase.h"
#include "retarget.h"

#define ADC_MAX (4096)
#define ADC_MAX_F (4096.0f)

SignalProcessBase& SignalProcessBase::init(My_Adc& Adc) {
    for (int i = 0; i < sample_num; ++i) {
        signal[i] = Adc.adc_buf[i];
    }
    samplerate = (float32_t)(Adc._f_in)/(Adc._htim->Instance->PSC + 1)/(Adc._htim->Instance->ARR + 1);
    sample_num = SIGNAL_BUFF_SIZE;
    return *this;
}

SignalProcessBase &SignalProcessBase::init(uint32_t *buffer, uint32_t samples) {
    for (int i = 0; i < samples; ++i) {
        signal[i] = buffer[i];
    }
    sample_num = samples;
    return *this;
}

void SignalProcessBase::debug()
{
    for(u32 i = 0; i < sample_num; i++)
    {
        printf("%lu,%f\n", i, signal[i]);
    }
}

void SignalProcessBase::read() {
    debug();
}

float32_t SignalProcessBase::get_max() {
    float32_t _max = 0.0f;
    arm_max_f32(signal, sample_num, &_max, NULL);
    return _max;
}

float32_t SignalProcessBase::get_min() {
    float32_t _min = 0.0f;
    arm_min_f32(signal, sample_num, &_min, NULL);
    return _min;
}

SignalProcessBase &SignalProcessBase::convert_to_mv() {
    for(uint32_t i = 0; i < sample_num; i++)
    {
        float32_t volt = 3300.0f * signal[i] / ADC_MAX_F;
        signal[i] =volt;
    }
    return *this;
}

SignalProcessBase &SignalProcessBase::normalize(uint32_t max_value) {
    for(uint32_t i = 0; i < sample_num; i++)
        signal[i] = signal[i]/max_value;
    return *this;
}

SignalProcessBase &SignalProcessBase::deal_DC() {
    float32_t mean = 0;
    for(uint32_t i = 0; i < sample_num; i++)
    {
        mean += signal[i];
    }
    mean /= sample_num;
    for(uint32_t i = 0; i < sample_num; i++)
    {
        signal[i] -= mean;
    }

    return *this;
}

float32_t SignalProcessBase::get_samplerate() {
    return samplerate;
}

uint32_t convert_to_analog_mv(float32_t num) {
    uint32_t volt = 3300 * num;
    volt = volt >> 12;
    return volt;
}


