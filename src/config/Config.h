#pragma once

#include "Sdram.h"

struct Config
{
    stmcmp::SdramConfig sdram;
    stmcmp::TerminalConfig terminal;
};

inline Config defaultConfig()
{
    return Config {
        .sdram = MT48LC2M32B2(),
        .terminal = {
            .baudrate = 115200,
        },
    };
}
