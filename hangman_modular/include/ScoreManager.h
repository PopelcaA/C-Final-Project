#pragma once
#include <string>
#include <vector>

class ScoreManager {
    std::string lbFile, histFile;
public:
    ScoreManager(const std::string& leaderboardFile,
                 const std::string& historyFile);
    void record(const std::string& player, int score,
                const std::vector<std::string>& words);
    void showLeaderboard() const;
    void showHistory() const;
};