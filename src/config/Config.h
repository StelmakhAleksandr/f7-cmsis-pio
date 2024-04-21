#pragma once

#include "Sdram.h"

struct Config
{
    SdramConfig sdram;
};

inline Config defaultConfig()
{
    return Config {
        .sdram = MT48LC2M32B2(),
    };
}
