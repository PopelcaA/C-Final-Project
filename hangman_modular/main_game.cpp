// main_game.cpp

#include "HangmanGame.h"
#include "ScoreManager.h"
#include "Colors.h"
#include "Config.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <ctime>

int main(int argc, char* argv[]) {
    enableAnsiColors();
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 1) Ensure the Data/ directory exists
    const std::string dataDir = "Data/";
    std::filesystem::create_directories(dataDir);

    // 2) Default file paths
    std::string wordsFile       = dataDir + "words.txt";
    std::string leaderboardFile = dataDir + "leaderboard.txt";
    std::string historyFile     = dataDir + "history.txt";

    // 3) Override if command-line args provided
    if (argc == 4) {
        wordsFile       = argv[1];
        leaderboardFile = argv[2];
        historyFile     = argv[3];
    } else if (argc != 1) {
        std::cerr << RED
                  << "Usage: hangman_game [words_file leaderboard_file history_file]\n"
                  << RESET;
        return 1;
    }

    try {
        ScoreManager sm(leaderboardFile, historyFile);
        HangmanGame game(sm);
        game.loadWords(wordsFile);
        game.mainMenu();
    } catch (const std::exception &e) {
        std::cerr << RED << "Fatal error: " << e.what() << RESET << "\n";
        return 1;
    }

    return 0;
}
