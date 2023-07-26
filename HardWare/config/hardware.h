//
// Created by Whisky on 2023/7/25.
//

#ifndef HELLOWORLD_HARDWARE_H
#define HELLOWORLD_HARDWARE_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/
//#include "ad9834.h"
//#include "Max262.h"
//#include "AD9959.h"
//#include "LMX2571.h"
//#include "AD9910.h"
#include "lcd.h"
#include "demos.h"
#include "touch.h"
#include "w25qxx.h"

void hardware_init();
#ifdef __cplusplus
}
/*---------------------------- C++ Scope ---------------------------*/
#include "Screen.h"
#endif

#endif //HELLOWORLD_HARDWARE_H
