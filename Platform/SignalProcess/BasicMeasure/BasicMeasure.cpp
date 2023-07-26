//
// Created by Whisky on 2023/5/23.
//

#include "BasicMeasure.h"

float32_t BasicMeasure::get_max() {
    return SignalProcessBase::get_max();
}

float32_t BasicMeasure::get_min() {
    return SignalProcessBase::get_min();
}

float32_t BasicMeasure::get_peak_to_peak() {
    float32_t _max = 0.0f;
    float32_t _min = 0.0f;
    arm_min_f32(signal, sample_num, &_min, NULL);
    arm_max_f32(signal, sample_num, &_max, NULL);
    return (_max - _min);
}

float32_t BasicMeasure::get_rms() {
    float32_t _rms_value = 0.0f;
    arm_rms_f32(signal, sample_num, &_rms_value);
    return _rms_value;
}

float32_t BasicMeasure::get_average(u32 n)
{
    float64_t sum = 0;
    for (u32 i = 0; i < n; ++i) {
        sum += signal[i];
    }
    sum = sum / (float32_t)n;
    return (float32_t)sum;
}

float32_t BasicMeasure::get_average() {
    return get_average(sample_num);
}

