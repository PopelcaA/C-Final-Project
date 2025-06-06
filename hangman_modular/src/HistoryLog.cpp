#include "HistoryLog.hpp"
#include <fstream>

HistoryLog::HistoryLog(const std::string& path) : path_(path)
{
    reload();
}
void HistoryLog::reload()
{
    list_.clear();
    std::ifstream f(path_);
    HistoryEntry e;
    while (f >> e.date >> e.time >> e.name >> e.gained >> e.total)
        list_.push_back(e);
}
void HistoryLog::append(const HistoryEntry& e)
{
    list_.push_back(e);
    std::ofstream out(path_, std::ios::app);
    out << e.date << ' ' << e.time << ' ' << e.name << ' '
        << e.gained << ' ' << e.total << '\n';
}
