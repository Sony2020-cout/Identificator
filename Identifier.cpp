#include "Identifier.h"
#include "IdentifierGroup.h"
#include "IdentifierExceptions.h"

using namespace std;

Identifier::Identifier(const string& str)
{
    size_t posBegin = 0;
    size_t posEnd = str.find(groupSeparator_, posBegin);

    while(string::npos != posEnd)
    {
        identifierGroups_.push_back(IdentifierGroup(str.substr(posBegin, posEnd - posBegin)));
        posBegin = posEnd + 1;
        posEnd = str.find(groupSeparator_, posBegin);
    }

    identifierGroups_.push_back(IdentifierGroup(str.substr(posBegin)));

    if(identifierGroups_.size() > maxGroupCount_)
    {
      throw InvalidIdentifierException("Too many groups in identifier!");
    }
}

void Identifier::increase()
{
    IdentifierGroups::reverse_iterator i = identifierGroups_.rbegin();

    for(; identifierGroups_.rend() != i; ++i)
    {
        IdentifierGroup& identifierGroup = *i;

        identifierGroup.increase();

        if(identifierGroup.getString() != IdentifierGroup::getZero())
        {
            break;
        }
    }

    if(identifierGroups_.rend() == i)
    {
        addNewGroup_();
    }
}

string Identifier::getString() const
{
    string result;
    IdentifierGroups::const_iterator i = identifierGroups_.begin();

    // identifierGroups_ всегда содержит хотя бы одну группу
    while(true)
    {
        result += i->getString();
        ++i;

        if(identifierGroups_.end() == i)
        {
            break;
        }

        result.push_back(groupSeparator_);
    }

    return result;
}

void Identifier::addNewGroup_()
{
    // первая группа была инкрементирована
  if(identifierGroups_.front().getString() == IdentifierGroup::getZero())
    {
        // добавляем в начало последовательности новую группу
        if(identifierGroups_.size() < maxGroupCount_)
        {
            identifierGroups_.push_front(IdentifierGroup(IdentifierGroup::getZero()));
        }
        else
        {
            throw EndOfSequenceException();
        }

    }
}
