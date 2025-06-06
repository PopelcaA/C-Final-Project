#ifndef HISTORY_LOG_HPP
#define HISTORY_LOG_HPP

#include <string>
#include <vector>

struct HistoryEntry
{
    std::string date;   // YYYY-MM-DD
    std::string time;   // HH:MM
    std::string name;
    int         gained  = 0;
    int         total   = 0;
};

class HistoryLog
{
public:
    explicit HistoryLog(const std::string& path = "history.txt");

    const std::vector<HistoryEntry>& entries() const noexcept { return list_; }
    void append(const HistoryEntry& e);     // also save to file
    void reload();

private:
    std::string               path_;
    std::vector<HistoryEntry> list_;
};

#endif // HISTORY_LOG_HPP
