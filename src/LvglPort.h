#pragma once

#include "lvgl.h"
#include "stmcmpf7/stmcmp.h"

class LvglPort
{
public:
    LvglPort(const stmcmp::LcdConfig& config);
    void setup();

private:
    void setupDisplayDriver();
    void setupTouchDriver();
    stmcmp::LcdConfig m_config;
};
