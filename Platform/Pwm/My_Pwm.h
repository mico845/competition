//
// Created by Whisky on 2023/5/23.
//

#ifndef HELLOWORLD_MY_PWM_H
#define HELLOWORLD_MY_PWM_H
#include "SignalPeripheral.h"


#endif //HELLOWORLD_MY_PWM_H
class My_Pwm: public SignalPeripheral{
public:
    My_Pwm(TIM_HandleTypeDef* htim, uint8_t channel = TIM_CHANNEL_1) :
            SignalPeripheral(htim) , _channel(channel){ }
    ~My_Pwm() = default;

    void start() override;
    void stop() override;
    My_Pwm& set_duty(float duty);
    My_Pwm& set_freq(uint32_t freq);
    void calc_tim_arr_psc() override;

private:
    float _duty = 0.5;
    uint8_t _channel = TIM_CHANNEL_1;
};