#include "AdminTool.hpp"
#include <iostream>
#include <exception>

AdminTool::AdminTool(WordRepository& d, Leaderboard& lb, HistoryLog& h)
    : dict_(d), lb_(lb), hist_(h) {}

void AdminTool::print_usage()
{
    std::cout <<
      "Commands:\n"
      "  list_words\n"
      "  add_word <word>\n"
      "  delete_word <word>\n"
      "  view_leaderboard\n"
      "  reset_leaderboard\n"
      "  view_history\n";
}

int AdminTool::dispatch(int argc, char** argv)
{
    if (argc < 2) { print_usage(); return 1; }
    std::string cmd = argv[1];

    try
    {
        if (cmd == "list_words")          list_words(dict_);
        else if (cmd == "add_word" && argc == 3)
        {
            if (!dict_.add(argv[2]))
                std::cout << "Failed – invalid or duplicate\n";
        }
        else if (cmd == "delete_word" && argc == 3)
        {
            if (!dict_.erase(argv[2]))
                std::cout << "Word not found\n";
        }
        else if (cmd == "view_leaderboard")   list_leaderboard(lb_);
        else if (cmd == "reset_leaderboard")  { lb_.reset(); std::cout << "Reset ok\n"; }
        else if (cmd == "view_history")       list_history(hist_);
        else { print_usage(); return 1; }
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 2;
    }
    return 0;
}

void AdminTool::list_words(const WordRepository& d)
{
    std::cout << "--- words.txt ---\n";
    int n = 1;
    for (const auto& w : d.list())
        std::cout << n++ << ". " << w << '\n';
}
void AdminTool::list_leaderboard(const Leaderboard& lb)
{
    std::cout << "--- leaderboard ---\n";
    int r = 1;
    for (const auto& p : lb.table())
        std::cout << r++ << ". " << p.name << " " << p.score << '\n';
}
void AdminTool::list_history(const HistoryLog& h)
{
    std::cout << "--- history ---\n";
    for (const auto& e : h.entries())
        std::cout << e.date << ' ' << e.time << ' ' << e.name
                  << " +" << e.gained << " => " << e.total << '\n';
}
