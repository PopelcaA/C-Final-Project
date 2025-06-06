#include "WordRepository.hpp"
#include <fstream>
#include <algorithm>
#include <random>

WordRepository::WordRepository(const std::string& path) : path_(path)
{
    reload();
}
void WordRepository::reload()
{
    words_.clear();
    std::ifstream f(path_);
    for (std::string w; f >> w;)
        words_.push_back(w);
}
void WordRepository::save() const
{
    std::ofstream out(path_);
    for (const auto& w : words_) out << w << '\n';
}
bool WordRepository::add(const std::string& w)
{
    if (w.empty() ||
        !std::all_of(w.begin(), w.end(),
                     [](unsigned char c){ return std::islower(c); }) ||
        std::find(words_.begin(), words_.end(), w) != words_.end())
        return false;

    words_.push_back(w);
    save();
    return true;
}
bool WordRepository::erase(const std::string& w)
{
    auto it = std::remove(words_.begin(), words_.end(), w);
    if (it == words_.end()) return false;
    words_.erase(it, words_.end());
    save();
    return true;
}
std::string WordRepository::random_word() const
{
    if (words_.empty()) return {};
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, words_.size() - 1);
    return words_[dist(rng)];
}
