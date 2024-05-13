#pragma once

#include "stmcmpf7/stmcmp.h"

inline std::vector<stmcmp::GpioBuilder> ltdcPins()
{
    using namespace stmcmp;
    return {
        PI15.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R0
        PJ0.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R1
        PJ1.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R2
        PJ2.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R3
        PJ3.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R4
        PJ4.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R5
        PJ5.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R6
        PJ6.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_R7
        PJ7.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G0
        PJ8.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G1
        PJ9.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G2
        PJ10.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G3
        PJ11.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G4
        PK0.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G5
        PK1.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G6
        PK2.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_G7
        PE4.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B0
        PJ13.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B1
        PJ14.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B2
        PJ15.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B3
        PG12.setAlternateFunction(9).setSpeed(PinSpeed::VeryHigh), // LCD_B4
        PK4.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B5
        PK5.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B6
        PK6.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_B7
        PI9.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_VSYNC
        PI10.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_HSYNC
        PI14.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_CLK
        PK7.setAlternateFunction(14).setSpeed(PinSpeed::VeryHigh), // LCD_DE
        PH1.setModer(PinModer::Input)
    };
}

inline stmcmp::LcdConfig lcd()
{
    using namespace stmcmp;
    return {
        .ltdcPins = ltdcPins(),
        .displayButton = PI12,
        .backLight = PK3,
        .activeWidth = 480,
        .activeHeight = 272,
        .frameRate = 60,
        .horizontalBackPorch = 13,
        .horizontalFrontPorch = 30,
        .verticalFrontPorch = 2,
        .verticalBackPorch = 2,
        .horizontalSync = 41,
        .verticalSync = 10,
        .horizontalSyncPolarity = false,
        .verticalSyncPolarity = false,
        .noDataEnablePolarity = false,
        .pixelClockPolarity = false,
        .layers = {
            {
                LayerConfig {
                    .layer = LTDC_Layer1,
                    .format = LayerFormat::ARGB8888,
                    .allocator = AllocatorType::SDRAM,
                    .useSwapBuffers = true,
                },
            },
        },
    };
}