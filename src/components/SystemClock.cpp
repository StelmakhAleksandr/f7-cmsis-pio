#include "SystemClock.h"

#include "stm32f746xx.h"

volatile uint32_t SystemClock::s_tickCount = 0;

extern "C" void SysTick_Handler()
{
    SystemClock::s_tickCount = SystemClock::s_tickCount + 1;
}

SystemClock* SystemClock::instance()
{
    static SystemClock instance;
    return &instance;
}

void SystemClock::delay_ms(uint32_t us)
{
    int start = s_tickCount;
    while ((s_tickCount - start) < us)
        ;
}

SystemClock::SystemClock()
{
    SysTick->LOAD = 216000000 / 1000 - 1;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}
