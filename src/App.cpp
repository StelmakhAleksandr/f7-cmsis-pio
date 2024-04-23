#include "App.h"

#include "config/Config.h"
#include "stmcmpf7/stmcmp.h"
#include <vector>

namespace stmapp {

App::App()
    : m_config(defaultConfig())
{
    using namespace stmcmp;
    auto clocks = ClocksBuilder()
                      .setHse(25_MHz)
                      .setSysclk(216_MHz)
                      .setHclk(216_MHz)
                      .setPclk1(54_MHz)
                      .setPclk2(108_MHz)
                      .build();
    Terminal::instance()->setup(m_config.terminal, clocks);
    SystemClock::instance()->setup(clocks);
    SdRam::instance()->setup(m_config.sdram);
}

void App::run()
{
    using namespace stmcmp;
    auto led = PI1.setModer(PinModer::Output).build();
    // SdRam::instance()->testMemory();

    while (true) {
        std::cout << "HELLO" << std::endl;
        stmcmp::printf("Yeah = %x \r\n", 0xFA);
        led.toggle();
        SystemClock::instance()->delay(std::chrono::seconds(1));
    }
}

};