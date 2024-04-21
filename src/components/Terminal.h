#pragma once

#include <iostream>
#include <streambuf>
#include <string>

namespace stmapp {

void printf(const char* format, ...);

class Terminal : public std::streambuf
{
public:
    static Terminal* instance();
    void send(const std::string& msg);
    void setup();
    void run();

protected:
    virtual int_type overflow(int_type c) override
    {
        sendChar(static_cast<char>(c));
        return c;
    }

private:
    Terminal() = default;
    void sendChar(char c);
};

};