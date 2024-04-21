#pragma once

#include "config/Config.h"

namespace stmapp {

class App
{
public:
    App();
    void run();

private:
    Config m_config;
};

};