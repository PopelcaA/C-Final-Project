#ifndef WORD_REPOSITORY_HPP
#define WORD_REPOSITORY_HPP

#include <string>
#include <vector>

class WordRepository
{
public:
    explicit WordRepository(const std::string& path = "words.txt");
    const std::vector<std::string>& list() const noexcept { return words_; }

    bool  add   (const std::string& w);   // true if added
    bool  erase (const std::string& w);   // true if removed
    void  reload();                       // re-read file
    std::string random_word() const;      // "" if empty

private:
    std::string              path_;
    std::vector<std::string> words_;
    void save() const;
};

#endif // WORD_REPOSITORY_HPP
