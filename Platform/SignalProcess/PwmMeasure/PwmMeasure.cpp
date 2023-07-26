//
// Created by Whisky on 2023/5/23.
//

#include "PwmMeasure.h"
#include <string.h>
#include "retarget.h"

PwmMeasure* pwmmeasure_instance1;

TIM_HandleTypeDef *__PwmMeasure_htim;
uint8_t __PwmMeasure_channel;

__IO uint32_t TIM_TIMEOUT_COUNT = 0;			///< 定时器定时溢出计数
uint32_t TIM_CAPTURE_BUF[3]   = {0, 0, 0};		///< 分别存储上升沿计数、下降沿计数、下个上升沿计数
__IO uint8_t TIM_CAPTURE_STA = 0;			///< 状态标记

PwmMeasure& PwmMeasure::init(uint32_t f_out, uint64_t f_in) {
    SignalPeripheral::init(f_out, f_in);
    pwmmeasure_instance1 = this;
    return *this;
}

void PwmMeasure::calc_tim_arr_psc() {
    float _psc = (float )_f_in/ (float )_f_out;
    if (_psc >= 65535)
        _psc = 65535;
    _htim->Instance->PSC = (u16)_psc + 1;
    _htim->Instance->ARR = 0XFFFF;
}

void PwmMeasure::start() {
    pwm_is_finished = false;
    calc_tim_arr_psc();
    TIM_CAPTURE_STA = 0;
    TIM_TIMEOUT_COUNT = 0;
    __HAL_TIM_SET_COUNTER(_htim, 0);										// 清除定时器2现有计数
    memset(TIM_CAPTURE_BUF, 0, sizeof(TIM_CAPTURE_BUF));						        // 清除捕获计数
    __HAL_TIM_SET_CAPTUREPOLARITY(_htim, _channel, TIM_INPUTCHANNELPOLARITY_RISING);	// 设置为上升沿触发
    HAL_TIM_Base_Start_IT(_htim);												        // 启动定时器更新中断
    HAL_TIM_IC_Start_IT(_htim, _channel);									            // 启动捕获中断
    TIM_CAPTURE_STA++;
}

void PwmMeasure::stop() {
    HAL_TIM_Base_Stop_IT(_htim);
    HAL_TIM_IC_Stop_IT(_htim, _channel);
}

void PwmMeasure::debug() {
    printf("\r\n\r\n");
    printf("################################# START #########################################\r\n");
    printf("High:       %lu us\r\n", high );
    printf("Period:     %lu us\r\n", cycle );
    printf("duty:     %f %%\r\n", duty );
    printf("Freq:       %f  Hz\r\n", freq);
    printf("################################## END ##########################################\r\n\r\n");
}

bool PwmMeasure::is_finished() {
    if (pwm_is_finished)
    {
        pwm_is_finished = false;
        return true;
    }
    else
        return pwm_is_finished;
}

uint32_t PwmMeasure::get_time_high() {
    return high;
}

uint32_t PwmMeasure::get_cycle_high() {
    return cycle;
}

float32_t PwmMeasure::get_duty() {
    return duty;
}

float32_t PwmMeasure::get_freq() {
    return freq;
}


#ifdef ENABLE_PWMMEASURE
/// 定时器时间溢出回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == pwmmeasure_instance1->_htim->Instance)
    {
        TIM_TIMEOUT_COUNT++;										// 溢出次数计数
    }
}

///< 输入捕获回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == pwmmeasure_instance1->_htim->Instance)
    {
        switch (TIM_CAPTURE_STA)
        {
            case 1:
            {
                //               printf("准备捕获下降沿...\r\n");
                TIM_CAPTURE_BUF[0] = HAL_TIM_ReadCapturedValue(htim, __PwmMeasure_channel) + TIM_TIMEOUT_COUNT * 0xFFFF;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, __PwmMeasure_channel, TIM_INPUTCHANNELPOLARITY_FALLING);					// 设置为下降沿触发
                TIM_CAPTURE_STA++;
                break;
            }
            case 2:
            {
//                printf("准备捕获下个上升沿...\r\n");
                TIM_CAPTURE_BUF[1] = HAL_TIM_ReadCapturedValue(htim, __PwmMeasure_channel) + TIM_TIMEOUT_COUNT * 0xFFFF;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, __PwmMeasure_channel, TIM_INPUTCHANNELPOLARITY_RISING);					// 设置为上升沿触发
                TIM_CAPTURE_STA++;
                break;
            }
            case 3:
            {
                //             printf("捕获结束...\r\n");
                //              printf("# end ----------------------------------------------------\r\n");
                TIM_CAPTURE_BUF[2] = HAL_TIM_ReadCapturedValue(htim, __PwmMeasure_channel) + TIM_TIMEOUT_COUNT * 0xFFFF;
                HAL_TIM_IC_Stop_IT(htim, __PwmMeasure_channel);									// 停止捕获
                HAL_TIM_Base_Stop_IT(htim);												// 停止定时器更新中断
                TIM_CAPTURE_STA++;
                pwmmeasure_instance1->high  = TIM_CAPTURE_BUF[1] - TIM_CAPTURE_BUF[0];
                pwmmeasure_instance1->cycle = TIM_CAPTURE_BUF[2] - TIM_CAPTURE_BUF[0];
                pwmmeasure_instance1->duty = (float32_t)pwmmeasure_instance1->high/(float32_t)pwmmeasure_instance1->cycle;
                pwmmeasure_instance1->freq = 1.0 / (((float32_t)pwmmeasure_instance1->cycle) / 1000000.0);
#ifdef PWM_DEBUG
                debug();
#endif
                pwmmeasure_instance1->pwm_is_finished = true;
                break;
            }
            default:
                break;
        }
    }
}

#endif