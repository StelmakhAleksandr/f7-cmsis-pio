#include "App.h"

#include "config/Config.h"
#include "stmcmpf7/stmcmp.h"
#include <vector>

#include "demos/lv_demos.h"
#include "lvgl.h"

namespace stmapp {

App::App()
    : m_config(defaultConfig())
    , m_led(stmcmp::PI1.setModer(stmcmp::PinModer::Output).build())
    , m_lvglPort(m_config.lcd)
{
    using namespace stmcmp;
    auto clocks = ClocksBuilder()
                      .setHse(25_MHz)
                      .setSysclk(216_MHz)
                      .setHclk(216_MHz)
                      .setPclk1(54_MHz)
                      .setPclk2(108_MHz)
                      .build();
    terminal()->setup(m_config.terminal, clocks);
    sysClock()->setup(clocks);
    sdram()->setup(m_config.sdram);
    lcd()->setup(m_config.lcd);
    touch()->setup(m_config.touch);
}

void App::measureFunc(std::function<void()> func, std::string msg)
{
    auto start = sysClock()->ticks();
    func();
    auto finish = sysClock()->ticks();
    stmcmp::printf("%s start = %d finish = %d res = %d\r\n", msg.c_str(), start, finish, finish - start);
}

void App::run()
{
    using namespace stmcmp;
    lcd()->backLightOn();
    lcd()->on();
    m_lvglPort.setup();

    lv_demo_benchmark();

    while (true) {
        lv_timer_handler();
        // sysClock()->delay(std::chrono::milliseconds(2));
    }
}
};