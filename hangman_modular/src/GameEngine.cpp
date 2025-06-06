#include "GameEngine.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#ifdef _WIN32
#include <windows.h>
#endif

/* static helpers ---------------------------------------------------------- */
static constexpr const char* HEAD = "  O   |";
static constexpr const char* GALLOWS[] = {
    "  +---+",
    "  |   |",
    "      |",
    "      |",
    "      |",
    "========"
};
void GameEngine::draw_hangman(int wrong)
{
    using std::cout;
    cout << "\033[38;5;214m";
    cout << GALLOWS[0] << '\n' << GALLOWS[1] << '\n';
    cout << (wrong >= 1 ? HEAD : "      |") << '\n';

    char l = wrong >= 2 ? '/' : ' ';
    char b = wrong >= 1 ? '|' : ' ';
    char r = wrong >= 3 ? '\\' : ' ';
    cout << ' ' << l << b << r << "  |\n";

    char l2 = wrong >= 4 ? '/' : ' ';
    char r2 = wrong >= 5 ? '\\' : ' ';
    cout << ' ' << l2 << ' ' << r2 << "  |\n";
    cout << GALLOWS[5] << "\n\033[0m";
}
std::string GameEngine::mask_word(const std::string& w,
                                  const std::vector<bool>& flags)
{
    std::string m;
    for (std::size_t i = 0; i < w.size(); ++i)
        m.push_back(flags[i] ? w[i] : '_');
    return m;
}

/* ctor -------------------------------------------------------------------- */
GameEngine::GameEngine(WordRepository& d, Leaderboard& lb, HistoryLog& h)
    : dict_(d), lb_(lb), hist_(h) {}

/* play_loop --------------------------------------------------------------- */
void GameEngine::play_round()
{
    using std::cin; using std::cout;

    if (dict_.list().empty())
    {
        cout << "\033[31mNo words available – ask Student 1 to add some.\033[0m\n";
        return;
    }

    cout << "Player name (letters only): ";
    std::string player;
    cin >> player;

    int session_score = 0;
    for (bool keep_playing = true; keep_playing; )
    {
        std::string secret = dict_.random_word();
        int wrong = 0;
        std::vector<bool> flags(secret.size(), false);

        for (std::size_t i = 0; i < secret.size(); ++i)
            if (secret[i] == secret.front() || secret[i] == secret.back())
                flags[i] = true;

        std::string tried;
        while (wrong < 6)
        {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
            draw_hangman(wrong);

            cout << "Word : \033[36m" << mask_word(secret, flags) << "\033[0m\n"
                 << "Miss : " << tried << "\n"
                 << "1) letter  2) word  3) quit\n> ";

            int opt; if (!(cin >> opt)) return;

            if (opt == 1)
            {
                char c; cout << "letter: "; cin >> c; c = std::tolower(c);
                if (!std::isalpha(static_cast<unsigned char>(c))) continue;
                if (tried.find(c) != std::string::npos) continue;

                bool hit = false;
                for (std::size_t i = 0; i < secret.size(); ++i)
                    if (secret[i] == c) { flags[i] = true; hit = true; }

                if (!hit) { tried += c; ++wrong; }
            }
            else if (opt == 2)
            {
                std::string guess; cout << "word: "; cin >> guess;
                if (guess == secret)
                    flags.assign(secret.size(), true);
                else { ++wrong; tried += '!'; }
            }
            else return;

            if (std::all_of(flags.begin(), flags.end(), [](bool b){ return b; }))
            {
                int pts = static_cast<int>(secret.size());
                session_score += pts;
                cout << "\033[32mCorrect! +" << pts << " pts\033[0m\n"
                     << "Continue (y/n)? ";
                char ans; cin >> ans;
                keep_playing = (ans == 'y' || ans == 'Y');
                break;
            }
        }

        if (wrong >= 6)
        {
            cout << "\033[31mGame over – word was " << secret << "\033[0m\n";
            keep_playing = false;
        }
    }

    lb_.update(player, session_score);
    hist_.append({today_date(), current_time(), player,
                  session_score,
                  std::find_if(lb_.table().begin(), lb_.table().end(),
                               [&](const Player& p){return p.name==player;})->score});

    cout << "Session score: " << session_score << '\n';
}
