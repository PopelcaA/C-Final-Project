#include "AdminMenu.h"
#include "Colors.h"
#include <string>
#include <filesystem>

int main() {
    enableAnsiColors();

    std::string dataDir  = "Data/";
    // ensure Data/ directory exists
    std::filesystem::create_directories(dataDir);

    std::string wordFile = dataDir + "words.txt";
    std::string lbFile   = dataDir + "leaderboard.txt";
    std::string histFile = dataDir + "history.txt";

    AdminMenu::run(wordFile, lbFile, histFile);
    return 0;
}
