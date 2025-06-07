#include "HangmanGame.h"
#include "Colors.h"
#include "InputHandler.h"
#include "Config.h"

#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

HangmanGame::HangmanGame(ScoreManager& mgr)
  : scoreMgr(mgr)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void HangmanGame::loadWords(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open " + filename);
    }
    words.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    if (words.empty()) {
        throw std::runtime_error(filename + " is empty");
    }
}

void HangmanGame::mainMenu() {
    while (true) {
        std::cout << ORANGE
                  << "=== HANGMAN GAME ===\n"
                  << "1) Start Game\n"
                  << "2) Admin\n"
                  << "3) Leaderboard\n"
                  << "4) History\n"
                  << "5) Exit\n"
                  << "Choice: "
                  << RESET;
        int opt = InputHandler::getInt(1, 5);
        switch (opt) {
            case 1:
                playSession();
                break;
            case 2:
                std::system("hangman_admin.exe");
                return;
            case 3:
                scoreMgr.showLeaderboard();
                break;
            case 4:
                scoreMgr.showHistory();
                break;
            case 5:
                return;
        }
    }
}

void HangmanGame::drawHangman(int wrong) const {
    std::cout << ORANGE
              << " +---+\n"
              << "  |   |\n"
              << "  " << (wrong >= 1 ? "O" : " ") << "   |\n "
              << (wrong >= 2 ? "/" : " ")
              << (wrong >= 1 ? "|" : " ")
              << (wrong >= 3 ? "\\" : " ") << "  |\n "
              << (wrong >= 4 ? "/" : " ")
              << (wrong >= MAX_WRONG ? "--" : " ") << "   |\n"
              << "      |\n"
              << "========\n"
              << RESET;
}

void HangmanGame::playSession() {
    if (words.empty()) return;

    int score = 0;
    std::vector<std::string> completedWords;

    while (true) {
        std::string secret = words.at(std::rand() % words.size());
        int len = static_cast<int>(secret.size());
        std::vector<bool> revealed(len, false);

        // reveal first and last (case-insensitive)
        char first = static_cast<char>(std::tolower(secret.front()));
        char last  = static_cast<char>(std::tolower(secret.back()));
        for (int i = 0; i < len; ++i) {
            char c = static_cast<char>(std::tolower(secret[i]));
            if (c == first || c == last) revealed[i] = true;
        }

        int shown = std::count(revealed.begin(), revealed.end(), true);
        int wrong = 0;
        std::string wrongs;

        while (true) {
            drawHangman(wrong);
            std::cout << RED << "Wrong: " << wrongs << "\n" << RESET;
            for (int i = 0; i < len; ++i) {
                if (revealed[i])
                    std::cout << GREEN << secret[i] << " " << RESET;
                else
                    std::cout << ORANGE << "_ " << RESET;
            }
            std::cout << ORANGE
                      << "\nScore: " << score << "\n"
                      << "1) Guess Letter  2) Guess Word  3) Menu\n"
                      << "Choice: "
                      << RESET;
            int choice = InputHandler::getInt(1, 3);

            if (choice == 1) {
                char c = InputHandler::getLetter();
                bool already = (wrongs.find(c) != std::string::npos);
                for (int i = 0; !already && i < len; ++i)
                    if (revealed[i] && std::tolower(secret[i]) == c)
                        already = true;
                if (already) {
                    std::cout << RED << "You already guessed that letter.\n" << RESET;
                    continue;
                }
                bool hit = false;
                for (int i = 0; i < len; ++i) {
                    if (std::tolower(secret[i]) == c && !revealed[i]) {
                        revealed[i] = true;
                        ++shown;
                        hit = true;
                    }
                }
                if (!hit && wrong < MAX_WRONG) {
                    wrongs.push_back(c);
                    ++wrong;
                }
            }
            else if (choice == 2) {
                std::cout << ORANGE << "Enter full word: " << RESET;
                std::string guess = InputHandler::getWord();
                std::string lower = secret;
                std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
                if (guess != lower) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::string name;
                    std::cout << ORANGE
                              << "\nGame over! Your score: " << score << "\n"
                              << "Enter your name: "
                              << RESET;
                    std::getline(std::cin, name);
                    if (name.empty()) name = "Anonymous";
                    scoreMgr.record(name, score, completedWords);
                    return;
                }
                shown = len;
            }
            else {  // Menu
                std::cout << RED
                          << "Return to menu? All progress lost.\n"
                          << "1) Yes  2) No\n"
                          << "Choice: "
                          << RESET;
                if (InputHandler::getInt(1, 2) == 1) return;
                continue;
            }

            if (shown == len) {
                completedWords.push_back(secret);
                score += len;
                std::cout << ORANGE
                          << "Correct! +" << len << " points.\n"
                          << "1) Continue  2) Menu\n"
                          << "Choice: "
                          << RESET;
                int next = InputHandler::getInt(1, 2);
                if (next == 2) {
                    std::cout << RED
                              << "Return to menu? All progress lost.\n"
                              << "1) Yes  2) No\n"
                              << "Choice: "
                              << RESET;
                    if (InputHandler::getInt(1, 2) == 1)
                        return;
                }
                break;  // start next word
            }

            if (wrong >= MAX_WRONG) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << ORANGE
                          << "\nGame over! Your score: " << score << "\n"
                          << "Enter your name: "
                          << RESET;
                std::getline(std::cin, name);
                if (name.empty()) name = "Anonymous";
                scoreMgr.record(name, score, completedWords);
                return;
            }
        }
    }
}