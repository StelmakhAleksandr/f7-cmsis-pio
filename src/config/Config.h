#pragma once

#include "Lcd.h"
#include "Sdram.h"
#include "Touch.h"

struct Config
{
    stmcmp::SdramConfig sdram;
    stmcmp::TerminalConfig terminal;
    stmcmp::LcdConfig lcd;
    stmcmp::TouchConfig touch;
};

inline Config defaultConfig()
{
    return Config {
        .sdram = MT48LC2M32B2(),
        .terminal = {
            .baudrate = 115200,
        },
        .lcd = lcd(),
        .touch = touch(),
    };
}
