#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "IdentifierGroup.h"
#include <list>

// идентификатор - содержит список групп
// максимальное количество групп задается maxGroupCount_
class Identifier
{
public:
    Identifier(const std::string& str);

    void increase();

    std::string getString() const;

private:
    // добавить новую группу в начало списка
    void addNewGroup_();

    typedef std::list<IdentifierGroup> IdentifierGroups;

    // список групп
    IdentifierGroups identifierGroups_;

    // максимальное количество групп в идентификаторе
    static const size_t maxGroupCount_ = 10;

    // разделитель групп
    static const char groupSeparator_ = '-';
};

#endif
