//
// Created by Whisky on 2023/5/16.
//

#include "common_inc.h"

void Init()
{
    delay_init(144);
    RetargetInit(&huart1);
    hardware_init();

#ifdef UART_RECEIVE
    ENABLE_IDLECallback();
    UART_IDLE_RegisterCallback(USER_UART_RxCpltCallback);
    HAL_UART_Receive_DMA(&huart3, (uint8_t*)Rx_str, RX_STR_LEN);
#endif
}
