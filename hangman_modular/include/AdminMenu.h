#pragma once

#include <string>

class AdminMenu {
public:
    static void run(const std::string& wordFile,
                    const std::string& leaderboardFile,
                    const std::string& historyFile);

    static void showWordList     (const std::string& file);
    static void addWord          (const std::string& file);
    static void clearLeaderboard(const std::string& file);
    static void clearHistory    (const std::string& file);
};
