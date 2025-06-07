#include "ScoreManager.h"
#include "Colors.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

ScoreManager::ScoreManager(const std::string& leaderboardFile,
                           const std::string& historyFile)
    : lbFile(leaderboardFile), histFile(historyFile) {}

void ScoreManager::record(const std::string& player, int score,
                          const std::vector<std::string>& words) {
    std::ofstream lb(lbFile, std::ios::app);
    if (!lb) throw std::runtime_error("Cannot write to " + lbFile);
    lb << player << " " << score << "\n";

    std::ofstream hist(histFile, std::ios::app);
    if (!hist) throw std::runtime_error("Cannot write to " + histFile);
    hist << player << " | " << score << "\n\t";
    for (size_t i = 0; i < words.size(); ++i) {
        if (i) hist << " ";
        hist << words[i];
    }
    hist << "\n";
}

void ScoreManager::showLeaderboard() const {
    std::ifstream f(lbFile);
    if (!f) {
        std::cout << RED << "Cannot open " << lbFile << "\n" << RESET;
        return;
    }
    std::vector<std::pair<int,std::string>> v;
    std::string line;
    while (std::getline(f, line)) {
        auto pos = line.find_last_of(" \t");
        if (pos == std::string::npos) continue;
        try {
            int sc = std::stoi(line.substr(pos+1));
            v.emplace_back(sc, line);
        } catch(...) {}
    }
    std::sort(v.begin(), v.end(), [](auto &a, auto &b){ return a.first > b.first; });
    std::cout << ORANGE << "=== Leaderboard ===\n" << RESET;
    for (int i = 0; i < (int)v.size(); ++i)
        std::cout << ORANGE << (i+1) << ". " << v[i].second << "\n" << RESET;
    if (v.empty())
        std::cout << ORANGE << "(no entries)\n" << RESET;
    std::cout << ORANGE << "Press ENTER to continue..." << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ScoreManager::showHistory() const {
    std::ifstream f(histFile);
    if (!f) {
        std::cout << RED << "Cannot open " << histFile << "\n" << RESET;
        return;
    }
    std::string line, wordsLine;
    std::cout << ORANGE << "=== History ===\n" << RESET;
    while (std::getline(f, line)) {
        std::cout << ORANGE << line << "\n" << RESET;
        if (std::getline(f, wordsLine))
            std::cout << ORANGE << "\t" << wordsLine << "\n" << RESET;
    }
    std::cout << ORANGE << "Press ENTER to continue..." << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}