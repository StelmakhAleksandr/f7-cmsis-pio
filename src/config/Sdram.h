#pragma once

#include "stmcmpf7/stmcmp.h"
#include <cstddef>
#include <vector>

constexpr uintptr_t SDRAM_START = 0xC0000000;
constexpr size_t SDRAM_SIZE = 8388608U;
constexpr size_t SDRAM_BLOCK_SIZE = 1024;
constexpr size_t SDRAM_NUM_BLOCKS = SDRAM_SIZE / SDRAM_BLOCK_SIZE;

inline std::vector<stmcmp::GpioBuilder> fmcPins()
{
    using namespace stmcmp;
    return {
        PF0, // A0
        PF1, // A1
        PF2, // A2
        PF3, // A3
        PF4, // A4
        PF5, // A5
        PF12, // A6
        PF13, // A7
        PF14, // A8
        PF15, // A9
        PG0, // A10
        PG1, // A11
        PG4, // BA0
        PG5, // BA1
        PD14, // D0
        PD15, // D1
        PD0, // D2
        PD1, // D3
        PE7, // D4
        PE8, // D5
        PE9, // D6
        PE10, // D7
        PE11, // D8
        PE12, // D9
        PE13, // D10
        PE14, // D11
        PE15, // D12
        PD8, // D13
        PD9, // D14
        PD10, // D15
        PE0, // NBL0
        PE1, // NBL1
        PC3, // SDCKEn
        PG8, // SDCLK
        PG15, // SDNCAS
        PH3, // SDNEn
        PH5, // SDNWE
        PF11 // SDNRAS
    };
}

inline stmcmp::SdramConfig MT48LC2M32B2()
{
    using namespace stmcmp;
    return SdramConfig {
        .control = {
            .column = ColumnBits::Bits9,
            .dataWidth = DataWidth::Bits16,
            .bankCount = BankCount::Four,
            .casLatency = CasLatency::Latency3,
            .sdramClock = SdramClock::TwoHCLK,
            .burstRead = BurstRead::Enabled,
            .readPipe = ReadPipe::NoDelay,
        },
        .timing = {
            .modeRegToActive = SdramCycles::Cycles3,
            .exitSelfRefresh = SdramCycles::Cycles8,
            .activeToPrecharge = SdramCycles::Cycles5,
            .rowCycle = SdramCycles::Cycles8,
            .writeRecovery = SdramCycles::Cycles2,
            .rowPrecharge = SdramCycles::Cycles3,
            .rowToColumn = SdramCycles::Cycles3,
        },
        .mrd = {
            .casLatency = CasLatency::Latency3,
            .burstLength = BurstLength::Four,
            .burstType = BurstType::Sequential,
            .writeMode = WriteMode::SingleLocationAccess,
        },
        .autoRefresh = SdramCycles::Cycles9,
        .refreshTime = 538,
        .fmcPins = fmcPins(),
    };
}