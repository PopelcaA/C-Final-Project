#include <iostream>
#include "GameEngine.hpp"
#include "AdminTool.hpp"

int main(int argc, char** argv)
{
    WordRepository dict;
    Leaderboard    lb;
    HistoryLog     hist;

    // allow read‑only queries even from game exe
    if (argc > 1)
    {
        std::string cmd = argv[1];
        if (cmd == "view_leaderboard")
        {
            AdminTool::list_leaderboard(lb);
            return 0;
        }
        if (cmd == "view_history")
        {
            AdminTool::list_history(hist);
            return 0;
        }
        std::cerr << "Usage: " << argv[0] << " [view_leaderboard|view_history]\n";
        return 1;
    }

    GameEngine engine(dict, lb, hist);
    engine.play_round();
    return 0;
}
