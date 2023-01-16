#ifndef IDENTIFIER_GROUP_H
#define IDENTIFIER_GROUP_H

#include <string>

// группа идентификатора
// состоит из одной буквы и одной цифры
class IdentifierGroup
{
public:
    IdentifierGroup(const std::string& str, bool checkString = true);

    void increase();

    // возвращает строку с началом последовательности
    static const char* getZero() { return "A1"; }

    const std::string& getString() const
    {
        return string_;
    } 

private:
    void checkLength_();
    void checkLetter_();
    void checkNumber_();

    static bool getLetterValid_(char letter);
    static bool getNumberValid_(char number);

    void increaseLetter_();

    // возвращает true, если после инкрементирования число перешло разряд 9 -> 1
    bool increaseNumber_();

    // группа идентификатора
    std::string string_;
};

#endif
