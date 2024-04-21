#pragma once

#include <string>

class Terminal
{
public:
    static Terminal *instance();
    void send(const std::string &msg);
    void setup();
    void run();

private:
    Terminal();
};
