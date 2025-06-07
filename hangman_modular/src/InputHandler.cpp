#include "InputHandler.h"
#include "Colors.h"
#include <iostream>
#include <limits>
#include <cctype>

int InputHandler::getInt(int min, int max) {
    int choice;
    while (true) {
        if (!(std::cin >> choice) || choice < min || choice > max) {
            std::cin.clear();
            std::cout << RED
                      << "Invalid input. Enter a number between "
                      << min << " and " << max << ".\n"
                      << RESET;
            std::cout << ORANGE << "Choice: " << RESET;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}

char InputHandler::getLetter() {
    char c;
    while (true) {
        std::cout << ORANGE << "Enter letter: " << RESET;
        std::cin >> c;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::isalpha(c)) return std::tolower(c);
        std::cout << RED << "Only letters a-z allowed.\n" << RESET;
    }
}

std::string InputHandler::getWord() {
    std::string w;
    while (true) {
        std::cin >> w;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool ok = !w.empty();
        for (char &ch : w) {
            if (!std::isalpha(ch)) { ok = false; break; }
            ch = std::tolower(ch);
        }
        if (ok) return w;
        std::cout << RED << "Only letters a-z allowed.\n" << RESET;
    }
}