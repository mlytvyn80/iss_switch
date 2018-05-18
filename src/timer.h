#ifndef TIMER_H_
#define TIMER_H_

#include <inttypes.h>
#include <stdbool.h>

void MainTimerInit(void);
void TimerInterrupt_Handler();
uint32_t MainTimerGetMs(void);
uint32_t MainTimerSet(const uint32_t AddTimeMs);
bool MainTimerIsExpired(const uint32_t Timer);
uint32_t MainTimerSet(const uint32_t AddTimeMs);

#endif // TIMER_H_
