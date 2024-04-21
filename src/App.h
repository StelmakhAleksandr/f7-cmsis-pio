#pragma once

#include "config/Config.h"

class App
{
public:
    App();
    void run();

private:
    Config m_config;
};
