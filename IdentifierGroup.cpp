#include "IdentifierGroup.h"
#include "IdentifierExceptions.h"
#include <sstream>

using namespace std;

IdentifierGroup::IdentifierGroup(const string& str, bool checkString/* = true*/)
: string_(str)
{
    if(checkString)
    {
        checkLength_();
        checkLetter_();
        checkNumber_();
    }
}

void IdentifierGroup::increase()
{
    if(increaseNumber_())
    {
        increaseLetter_();
    }
}

void IdentifierGroup::checkLength_()
{
    if(2 != string_.length())
    {
        ostringstream os;

        os << "Identifier group [" << string_ << "] has invalid length!";

        throw InvalidIdentifierException(os.str().c_str());
    }
}

void IdentifierGroup::checkLetter_()
{
   if(!getLetterValid_(string_[0]))
    {
        ostringstream os;

        os << "Identifier group [" << string_ << "] has invalid letter!";

        throw InvalidIdentifierException(os.str().c_str());
    }
}

void IdentifierGroup::checkNumber_()
{
   if(!getNumberValid_(string_[1]))
    {
        ostringstream os;

        os << "Identifier group [" << string_ << "] has invalid number!";

        throw InvalidIdentifierException(os.str().c_str());
    }
}

bool IdentifierGroup::getLetterValid_(const char letter)
{
    return 'A' <= letter &&
           'Z' >= letter &&
           'D' != letter &&
           'F' != letter &&
           'G' != letter &&
           'J' != letter &&
           'M' != letter &&
           'Q' != letter &&
           'V' != letter;
}

bool IdentifierGroup::getNumberValid_(const char number)
{
    return '1' <= number &&
           '9' >= number;
}

void IdentifierGroup::increaseLetter_()
{
    char& letter = string_[0];

    ++letter;

    while(!getLetterValid_(letter))
    {
        ++letter;

        if('Z' < letter)
        {
            letter = 'A';
        }
    }
}

// возвращает true если число перешло разряд
bool IdentifierGroup::increaseNumber_()
{
    char& number = string_[1];

    ++number;

    bool result = '9' < number;

    if(result)
    {
        number = '1';
    }

    return result;
}
