#include "App.h"

#include "components/ClockManager.h"
#include "components/SdRam.h"
#include "components/SystemClock.h"
#include "components/Terminal.h"
#include "config/Config.h"
#include "drivers/Pins.h"
#include "stm32f746xx.h"
#include <vector>

namespace stmapp {

App::App()
    : m_config(defaultConfig())
{
    ClockManager::instance()->enableMaxClockSpeed();
    Terminal::instance()->setup();
    SdRam::instance()->setup(m_config.sdram);
}

void App::run()
{
    Terminal::instance()->run();
    auto led = PI1.setModer(PinModer::Output).build();
    // SdRam::instance()->testMemory();

    while (true) {
        std::cout << "HELLO" << std::endl;
        printf("Yeah = %x \r\n", 0xFA);
        led.toggle();
        SystemClock::instance()->delay_ms(1000);
    }
}

};