#include "timer.h"

#include <util/atomic.h>



static volatile uint32_t TimeMs = 0;

void MainTimerInit(void)
{
    TimeMs = 0;

    //TimerInit(); // SysTick_Config(SystemCoreClock / 1000);
}


void TimerInterrupt_Handler(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        TimeMs++;
    }
}

uint32_t MainTimerGetMs(void)
{
    return TimeMs;
}


uint32_t MainTimerSet(const uint32_t AddTimeMs)
{
    return TimeMs + AddTimeMs;
}

bool MainTimerIsExpired(const uint32_t Timer)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if ((TimeMs - Timer) < (1UL << 31)) return (Timer <= TimeMs);
    }

    return false;
}


