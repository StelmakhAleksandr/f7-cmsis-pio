#include "Terminal.h"

#include "drivers/Pins.h"
#include "stm32f746xx.h"

namespace {
constexpr int TerminalMaxSpeed = 108000000;
constexpr int TerminalBaudrate = 115200;
constexpr int TerminalBRR = TerminalMaxSpeed / TerminalBaudrate;
};

Terminal* Terminal::instance()
{
    static Terminal instance;
    return &instance;
}

void Terminal::send(const std::string& msg)
{
    USART1->ICR &= USART_ICR_TCCF;
    for (size_t i = 0; i < msg.size(); i++) {
        while (!(USART1->ISR & USART_ISR_TXE)) {
        };
        USART1->TDR = msg.at(i);
    }
    while (!(USART1->ISR & USART_ISR_TC)) {
    };
    USART1->ICR &= USART_ICR_TCCF;
}

void Terminal::setup()
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    PA9.setAlternateFunction(7)
        .setPull(PinPull::No)
        .setSpeed(PinSpeed::VeryHigh)
        .setType(PinType::PushPull)
        .build();

    // GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9_Msk)) | GPIO_MODER_MODER9_1;
    // GPIOA->AFR[1] = (GPIOA->AFR[1] & ~GPIO_AFRH_AFRH1_Msk) | 0b0111 << GPIO_AFRH_AFRH1_Pos;
    // GPIOA->OTYPER &= ~GPIO_OTYPER_OT9;
    // GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR9;
    // GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;

    GPIOB->MODER = (GPIOB->MODER & ~(GPIO_MODER_MODER7_Msk)) | (GPIO_MODER_MODER7_1);
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFRL7_Msk) | (0b0111 << GPIO_AFRL_AFRL7_Pos); // PB7 to AF7
    GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_7);
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEEDR7);
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR7);

    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR2 |= USART_CR2_RTOEN;
    USART1->BRR = TerminalBRR;
}

void Terminal::run()
{
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_TE;
}

Terminal::Terminal()
{
}
