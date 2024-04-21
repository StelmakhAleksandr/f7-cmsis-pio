#include "Terminal.h"

#include "drivers/Pins.h"
#include <cstdarg>
#include <cstdio>

namespace {
constexpr int TerminalMaxSpeed = 108000000;
constexpr int TerminalBaudrate = 115200;
constexpr int TerminalBRR = TerminalMaxSpeed / TerminalBaudrate;
};

namespace stmapp {

Terminal* Terminal::instance()
{
    static Terminal instance;
    return &instance;
}

void Terminal::send(const std::string& msg)
{
    for (char c : msg) {
        sendChar(c);
    }
}

void Terminal::setup()
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    PA9.setAlternateFunction(7)
        .setPull(PinPull::No)
        .setSpeed(PinSpeed::VeryHigh)
        .setType(PinType::PushPull)
        .build();
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR2 |= USART_CR2_RTOEN;
    USART1->BRR = TerminalBRR;
}

void Terminal::run()
{
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_TE;
    std::cout.rdbuf(this);
}

void Terminal::sendChar(char c)
{
    USART1->ICR &= USART_ICR_TCCF;
    while (!(USART1->ISR & USART_ISR_TXE)) {
    };
    USART1->TDR = c;
    while (!(USART1->ISR & USART_ISR_TC)) {
    };
}

void printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    Terminal::instance()->send(buffer);
}

};