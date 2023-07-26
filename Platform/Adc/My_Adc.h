//
// Created by Whisky on 2023/5/23.
//

#ifndef HELLOWORLD_MY_ADC_H
#define HELLOWORLD_MY_ADC_H

#include "SignalPeripheral.h"
#include <stdbool.h>
#include "Config.h"

//与实际对应通道无关，只是代表顺序
typedef enum
{
    My_Adc_Channel_No_1 = 0,
    My_Adc_Channel_No_2 ,
    My_Adc_Channel_No_3
}ADC_CHANNEL;

class SignalProcessBase;
class GraphWindows;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

class My_Adc: public SignalPeripheral {
public:
    My_Adc(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim) : SignalPeripheral(htim), _hadc(hadc) { }
    ~My_Adc() = default;

    My_Adc& init(uint32_t f_out, uint64_t f_in) override;
    void start() override;
    void stop() override;

    void read();
    bool is_finished();

    My_Adc& set_samplerate(uint32_t sample_rate);
    void get_signal(uint8_t channel_num, ADC_CHANNEL channel, uint32_t *buffer);
private:
    bool adc_finished = false;
    ADC_HandleTypeDef *_hadc;
    uint32_t adc_buf[ADC_BUFF_SIZE] = {0};
public:
    friend class SignalProcessBase;
    friend class GraphWindows;
    friend void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
};


#endif //HELLOWORLD_MY_ADC_H
