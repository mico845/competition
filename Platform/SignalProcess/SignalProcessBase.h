//
// Created by Whisky on 2023/5/23.
//

#ifndef HELLOWORLD_SIGNALPROCESSBASE_H
#define HELLOWORLD_SIGNALPROCESSBASE_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/
#include "arm_math.h"
#include "arm_const_structs.h"
#include "FFTInc.h"

#ifdef __cplusplus
}
/*---------------------------- C++ Scope ---------------------------*/
#include "EmbeddedSystem.h"
#include "My_Adc.h"
#include "retarget.h"


typedef enum
{
    FIR = 0,
    IIR,
}Filter_Type;

class GraphWindows;

class SignalProcessBase : public EmbeddedSystem
{
public:
    SignalProcessBase() = default;
    ~SignalProcessBase() = default;

    virtual SignalProcessBase& init(My_Adc& Adc);
    virtual SignalProcessBase& init(uint32_t *buffer, uint32_t samples);
    virtual SignalProcessBase& apply_windows();
    virtual SignalProcessBase& release_windows();
    virtual SignalProcessBase& fft_mag();
    virtual SignalProcessBase& fft_phase();
    virtual SignalProcessBase& fft_arm();
    virtual SignalProcessBase& ifft_arm();
    virtual SignalProcessBase& filter(Filter_Type type);
    virtual SignalProcessBase& convert_to_mv();
    virtual SignalProcessBase& normalize(uint32_t max_value = 4096);
    virtual SignalProcessBase& deal_DC();
    virtual float32_t get_max();
    virtual float32_t get_min();

    virtual float32_t get_samplerate();

    void read();
protected:
    float32_t signal[SIGNAL_BUFF_SIZE] = {0};
    uint32_t sample_num = SIGNAL_BUFF_SIZE;
    float32_t samplerate;
    virtual void debug();

public:
    friend class GraphWindows;
};

u32 convert_to_analog_mv(float32_t num);

#endif

#endif //HELLOWORLD_SIGNALPROCESSBASE_H
