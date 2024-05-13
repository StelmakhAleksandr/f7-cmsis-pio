#pragma once

#include "stmcmpf7/stmcmp.h"

inline stmcmp::TouchConfig touch()
{
    using namespace stmcmp;
    return {
        .button = PI13,
        .address = 0x38,
        .statusReg = 0x02,
        .firstXhReg = 0x03,
        .sizeStateReg = 6,
        .xBitmask = 0x0F,
        .yBitmask = 0x0F,
    };
}