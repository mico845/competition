//
// Created by Whisky on 2023/5/23.
//

#include "SignalPeripheral.h"
#include "retarget.h"
#include "arm_math.h"


void SignalPeripheral::calc_tim_arr_psc()
{
    float32_t Min_psc_freq = (float32_t)_f_in/65535;
    float32_t arr_f, psc_f;
    uint16_t arr, psc;

    if(_f_out == 0 || _f_in == 0 || _f_out > _f_in)
        return;
    else if (_f_out < Min_psc_freq/56)
    {
        psc_f = _f_in/10000 - 1;
        arr_f = 10000/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/55)
    {
        psc_f = 55;
        arr_f = _f_in/56/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/54)
    {
        psc_f = 54;
        arr_f = _f_in/55/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/53)
    {
        psc_f = 53;
        arr_f = _f_in/54/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/52)
    {
        psc_f = 52;
        arr_f = _f_in/53/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/51)
    {
        psc_f = 51;
        arr_f = _f_in/52/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/50)
    {
        psc_f = 50;
        arr_f = _f_in/51/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/49)
    {
        psc_f = 49;
        arr_f = _f_in/50/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/48)
    {
        psc_f = 48;
        arr_f = _f_in/49/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/47)
    {
        psc_f = 47;
        arr_f = _f_in/48/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/46)
    {
        psc_f = 46;
        arr_f = _f_in/47/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/45)
    {
        psc_f = 45;
        arr_f = _f_in/46/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/44)
    {
        psc_f = 44;
        arr_f = _f_in/45/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/43)
    {
        psc_f = 43;
        arr_f = _f_in/44/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/42)
    {
        psc_f = 42;
        arr_f = _f_in/43/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/41)
    {
        psc_f = 41;
        arr_f = _f_in/42/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/40)
    {
        psc_f = 40;
        arr_f = _f_in/41/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/39)
    {
        psc_f = 39;
        arr_f = _f_in/40/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/38)
    {
        psc_f = 38;
        arr_f = _f_in/39/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/37)
    {
        psc_f = 37;
        arr_f = _f_in/38/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/36)
    {
        psc_f = 36;
        arr_f = _f_in/37/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/35)
    {
        psc_f = 35;
        arr_f = _f_in/36/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/34)
    {
        psc_f = 34;
        arr_f = _f_in/35/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/33)
    {
        psc_f = 33;
        arr_f = _f_in/34/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/32)
    {
        psc_f = 32;
        arr_f = _f_in/33/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/31)
    {
        psc_f = 31;
        arr_f = _f_in/32/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/30)
    {
        psc_f = 30;
        arr_f = _f_in/31/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/29)
    {
        psc_f = 29;
        arr_f = _f_in/30/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/28)
    {
        psc_f = 28;
        arr_f = _f_in/29/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/27)
    {
        psc_f = 27;
        arr_f = _f_in/28/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/26)
    {
        psc_f = 26;
        arr_f = _f_in/27/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/25)
    {
        psc_f = 25;
        arr_f = _f_in/26/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/24)
    {
        psc_f = 24;
        arr_f = _f_in/25/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/23)
    {
        psc_f = 23;
        arr_f = _f_in/24/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/22)
    {
        psc_f = 22;
        arr_f = _f_in/23/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/21)
    {
        psc_f = 21;
        arr_f = _f_in/22/_f_out;
        --arr_f;
    }
    else if (_f_out <Min_psc_freq/20)
    {
        psc_f = 20;
        arr_f = _f_in/21/_f_out;
        --arr_f;
    }
    else if (_f_out <Min_psc_freq/19)
    {
        psc_f = 19;
        arr_f = _f_in/20/_f_out;
        --arr_f;
    }
    else if (_f_out <Min_psc_freq/18)
    {
        psc_f = 18;
        arr_f = _f_in/19/_f_out;
        --arr_f;
    }
    else if (_f_out <Min_psc_freq/18)
    {
        psc_f = 18;
        arr_f = _f_in/19/_f_out;
        --arr_f;
    }
    else if (_f_out <Min_psc_freq/17)
    {
        psc_f = 17;
        arr_f = _f_in/18/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/16)
    {
        psc_f = 16;
        arr_f = _f_in/17/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/15)
    {
        psc_f = 15;
        arr_f = _f_in/16/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/14)
    {
        psc_f = 14;
        arr_f = _f_in/15/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/13)
    {
        psc_f = 13;
        arr_f = _f_in/14/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/12)
    {
        psc_f = 12;
        arr_f = _f_in/13/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/11)
    {
        psc_f = 11;
        arr_f = _f_in/12/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/10)
    {
        psc_f = 10;
        arr_f = _f_in/11/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/9)
    {
        psc_f = 9;
        arr_f = _f_in/10/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/8)
    {
        psc_f = 8;
        arr_f = _f_in/9/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/7)
    {
        psc_f = 7;
        arr_f = _f_in/8/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/6)
    {
        psc_f = 6;
        arr_f = _f_in/7/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/5)
    {
        psc_f = 5;
        arr_f = _f_in/6/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/4)
    {
        psc_f = 4;
        arr_f = _f_in/5/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/3)
    {
        psc_f = 3;
        arr_f = _f_in/4/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq/2)
    {
        psc_f = 2;
        arr_f = _f_in/3/_f_out;
        --arr_f;
    }
    else if (_f_out < Min_psc_freq)
    {
        psc_f = 1;
        arr_f = _f_in/2/_f_out;
        --arr_f;
    }
    else
    {
        psc_f = 0;
        arr_f = _f_in/_f_out;
        --arr_f;
    }

    arr = round(arr_f);
    psc = round(psc_f);

    _htim->Instance->CNT = 0;
    _htim->Instance->ARR = arr;
    _htim->Instance->PSC = psc;


#ifdef TIM_DEBUG
    debug();
#endif
}

void SignalPeripheral::debug() {
    if (_f_in/(_htim->Instance->ARR +1)/(_htim->Instance->PSC +1) - _f_out < 0.5)
        ;
    else
    {
        printf("============\n");
        printf("freq: %lu\n",_f_out);
        printf("arr: %lu\n",_htim->Instance->ARR);
        printf("psc: %lu\n",_htim->Instance->PSC);
        printf("act_f: %f\n",(double)(_f_in/(_htim->Instance->ARR +1)/(_htim->Instance->PSC +1)));
    }
}

