#include "utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
    std::string now_str(const char* fmt)
    {
        std::time_t t = std::time(nullptr);
        std::tm      tm{};
    #ifdef _WIN32
        localtime_s(&tm, &t);
    #else
        localtime_r(&t, &tm);
    #endif
        std::ostringstream os;
        os << std::put_time(&tm, fmt);
        return os.str();
    }
}

std::string today_date()  { return now_str("%F"); }
std::string current_time(){ return now_str("%H:%M"); }
