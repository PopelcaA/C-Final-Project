#pragma once

#include <vector>
#include <string>
#include "ScoreManager.h"
#include "Config.h"

class HangmanGame {
public:
    explicit HangmanGame(ScoreManager& mgr);
    void loadWords(const std::string& filename);
    void mainMenu();
private:
    std::vector<std::string> words;
    ScoreManager& scoreMgr;
    void drawHangman(int wrong) const;
    void playSession();
};
