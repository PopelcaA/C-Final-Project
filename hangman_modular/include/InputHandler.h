#pragma once
#include <string>

class InputHandler {
public:
    static int getInt(int min, int max);
    static char getLetter();
    static std::string getWord();
};