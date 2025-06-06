#ifndef ADMIN_TOOL_HPP
#define ADMIN_TOOL_HPP

#include "WordRepository.hpp"
#include "Leaderboard.hpp"
#include "HistoryLog.hpp"

class AdminTool
{
public:
    AdminTool(WordRepository& d, Leaderboard& lb, HistoryLog& h);
    int dispatch(int argc, char** argv);      // returns 0 on success

    // expose helpers for game.exe
    static void list_words(const WordRepository&);
    static void list_leaderboard(const Leaderboard&);
    static void list_history(const HistoryLog&);

private:
    WordRepository& dict_;
    Leaderboard&    lb_;
    HistoryLog&     hist_;

    static void print_usage();
};

#endif // ADMIN_TOOL_HPP
