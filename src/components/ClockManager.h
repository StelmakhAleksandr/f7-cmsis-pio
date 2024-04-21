#pragma once

class ClockManager
{
public:
    static ClockManager* instance();
    void enableMaxClockSpeed();

private:
    ClockManager();
    void runHSE();
    void runPLL();
    void runPLLCLK();
    void setupPLL();
    void setupBusPrescalers();
    void setupFLASH();
};
