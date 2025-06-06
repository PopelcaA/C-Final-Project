#include "AdminTool.hpp"
#include "WordRepository.hpp"
#include "Leaderboard.hpp"
#include "HistoryLog.hpp"

int main(int argc, char** argv)
{
    WordRepository dict;
    Leaderboard    lb;
    HistoryLog     hist;

    AdminTool tool(dict, lb, hist);
    return tool.dispatch(argc, argv);
}
