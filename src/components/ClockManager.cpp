#include "ClockManager.h"

#include "stm32f746xx.h"

namespace {
constexpr int RCCMaxSpeedPLLN = 432;
constexpr int RCCMaxSpeedPLLM = 25;
};

ClockManager* ClockManager::instance()
{
    static ClockManager instance;
    return &instance;
}

void ClockManager::enableMaxClockSpeed()
{
    runHSE();
    setupPLL();
    runPLL();
    setupBusPrescalers();
    setupFLASH();
    runPLLCLK();
}

ClockManager::ClockManager()
{
}

void ClockManager::runHSE()
{
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0) {
    };
}

void ClockManager::runPLL()
{
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
    };
}

void ClockManager::runPLLCLK()
{
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0) {
    };
}

void ClockManager::setupPLL()
{
    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    RCC->PLLCFGR |= (RCCMaxSpeedPLLN << RCC_PLLCFGR_PLLN_Pos);
    RCC->PLLCFGR |= (RCCMaxSpeedPLLM << RCC_PLLCFGR_PLLM_Pos);
}

void ClockManager::setupBusPrescalers()
{
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;
}

void ClockManager::setupFLASH()
{
    FLASH->ACR |= FLASH_ACR_LATENCY_7WS;
}
