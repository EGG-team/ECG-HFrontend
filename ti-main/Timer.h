// Core library for code-sense - IDE-based
// Include application, user and local libraries
#include <Energia.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Timer.h>

#ifndef Timer_h
#define Timer_h

class Timer
{
private:
    Timer_Handle TimerHandle;
    
public:
    Timer();
    
    void begin(void (*timerFunction)(void), uint32_t timerPeriod_unit, uint32_t unit = 1000);

    void start();
    
    void stop();
};

#endif
