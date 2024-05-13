#pragma once

#include "LvglPort.h"
#include "config/Config.h"
#include <functional>

namespace stmapp {

class App
{
public:
    App();
    void run();
    static stmcmp::Lcd* lcd()
    {
        return stmcmp::Lcd::instance();
    }
    static stmcmp::Touch* touch()
    {
        return stmcmp::Touch::instance();
    }
    static stmcmp::Terminal* terminal()
    {
        return stmcmp::Terminal::instance();
    }
    static stmcmp::SdRam* sdram()
    {
        return stmcmp::SdRam::instance();
    }
    static stmcmp::SystemClock* sysClock()
    {
        return stmcmp::SystemClock::instance();
    }

private:
    Config m_config;
    stmcmp::GpioPin m_led;
    void measureFunc(std::function<void()> func, std::string msg);
    LvglPort m_lvglPort;
};

};