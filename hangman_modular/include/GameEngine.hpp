#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "WordRepository.hpp"
#include "Leaderboard.hpp"
#include "HistoryLog.hpp"

class GameEngine
{
public:
    GameEngine(WordRepository& dict, Leaderboard& lb, HistoryLog& hist);
    void play_round();   // interactive loop

private:
    WordRepository& dict_;
    Leaderboard&    lb_;
    HistoryLog&     hist_;

    // helpers
    static void draw_hangman(int wrong);
    static std::string mask_word(const std::string& w,
                                 const std::vector<bool>& flags);
};

#endif // GAME_ENGINE_HPP
