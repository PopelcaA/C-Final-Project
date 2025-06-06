#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

#include <string>
#include <vector>

struct Player
{
    std::string name;
    int         score = 0;
};

class Leaderboard
{
public:
    explicit Leaderboard(const std::string& path = "leaderboard.txt");

    const std::vector<Player>& table() const noexcept { return table_; }
    void update(const std::string& name, int add_points);
    void reset();
    void reload();

private:
    std::string         path_;
    std::vector<Player> table_;
    void save() const;
};

#endif // LEADERBOARD_HPP
