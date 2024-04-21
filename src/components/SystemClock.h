#pragma once

#include <chrono>

extern "C" void SysTick_Handler();

class SystemClock
{
    friend void SysTick_Handler();

public:
    static SystemClock* instance();
    void delay_ms(uint32_t us);

private:
    SystemClock();
    static volatile uint32_t s_tickCount;
};
