#include "Leaderboard.hpp"
#include <fstream>
#include <algorithm>

Leaderboard::Leaderboard(const std::string& path) : path_(path)
{
    reload();
}
void Leaderboard::reload()
{
    table_.clear();
    std::ifstream f(path_);
    std::string name; int score;
    while (f >> name >> score) table_.push_back({name, score});
}
void Leaderboard::save() const
{
    std::ofstream out(path_);
    for (const auto& p : table_) out << p.name << ' ' << p.score << '\n';
}
void Leaderboard::update(const std::string& name, int add_points)
{
    auto it = std::find_if(table_.begin(), table_.end(),
                           [&](const Player& p){ return p.name == name; });
    if (it == table_.end())
        table_.push_back({name, add_points});
    else
        it->score += add_points;

    std::sort(table_.begin(), table_.end(),
              [](const Player& a, const Player& b){ return a.score > b.score; });
    save();
}
void Leaderboard::reset()
{
    table_.clear();
    save();
}
