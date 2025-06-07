#include "AdminMenu.h"
#include "InputHandler.h"
#include "Colors.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <filesystem>
#include <cstdlib>
#include <regex>

void AdminMenu::run(const std::string& wordFile,
                    const std::string& leaderboardFile,
                    const std::string& historyFile)
{
    // ensure Data/ directory exists
    if (auto dir = std::filesystem::path(wordFile).parent_path(); !dir.empty())
        std::filesystem::create_directories(dir);

    while (true) {
        std::cout << ORANGE
                  << "=== HANGMAN ADMIN ===\n"
                  << "1) View Word List\n"
                  << "2) Add Word\n"
                  << "3) Clear Leaderboard\n"
                  << "4) Clear History\n"
                  << "5) Exit\n"
                  << "6) Start Game\n"
                  << "Choice: "
                  << RESET;

        int choice = InputHandler::getInt(1, 6);

        switch (choice) {
            case 1:
                showWordList(wordFile);
                break;
            case 2:
                addWord(wordFile);
                break;
            case 3:
                clearLeaderboard(leaderboardFile);
                break;
            case 4:
                clearHistory(historyFile);
                break;
            case 5:
                return;
            case 6: {
                std::cout << ORANGE << "Launching game...\n" << RESET;
                std::string cmd = "hangman_game.exe \"" +
                                  wordFile + "\" \"" +
                                  leaderboardFile + "\" \"" +
                                  historyFile + "\"";
                if (std::system(cmd.c_str()) != 0) {
                    std::cerr << RED << "Failed to launch game\n" << RESET;
                }
                return;
            }
        }

        std::cout << ORANGE
                  << "Press ENTER to continue..."
                  << RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void AdminMenu::showWordList(const std::string& file) {
    std::ifstream f(file);
    if (!f) {
        std::cout << RED << "Cannot open " << file << "\n" << RESET;
        return;
    }
    std::cout << ORANGE << "=== Word List ===\n" << RESET;
    int i = 1;
    std::string line;
    while (std::getline(f, line)) {
        std::cout << ORANGE << i++ << ". " << line << "\n" << RESET;
    }
}

void AdminMenu::addWord(const std::string& file) {
    // ensure Data/ directory exists
    if (auto dir = std::filesystem::path(file).parent_path(); !dir.empty())
        std::filesystem::create_directories(dir);

    static const std::regex alpha_only("^[A-Za-z]+$");
    std::string w;
    while (true) {
        std::cout << ORANGE << "Enter new word: " << RESET;
        if (!std::getline(std::cin, w)) {
            std::cin.clear();
            std::cout << RED << "Input error. Please try again.\n" << RESET;
            continue;
        }
        if (!std::regex_match(w, alpha_only)) {
            std::cout << RED
                      << "Only letters A-Z allowed. Please try again.\n"
                      << RESET;
            continue;
        }
        for (auto &ch : w)  // lowercase
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        break;
    }

    std::ofstream fout(file, std::ios::app);
    if (!fout) {
        std::cout << RED << "Cannot open " << file << "\n" << RESET;
        return;
    }
    fout << w << "\n";
}

void AdminMenu::clearLeaderboard(const std::string& file) {
    std::ofstream f(file, std::ios::trunc);
    if (!f) {
        std::cout << RED << "Cannot open " << file << " to clear\n" << RESET;
        return;
    }
    std::cout << ORANGE << "Leaderboard cleared.\n" << RESET;
}

void AdminMenu::clearHistory(const std::string& file) {
    std::ofstream f(file, std::ios::trunc);
    if (!f) {
        std::cout << RED << "Cannot open " << file << " to clear\n" << RESET;
        return;
    }
    std::cout << ORANGE << "History cleared.\n" << RESET;
}
