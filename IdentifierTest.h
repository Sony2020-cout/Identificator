#ifndef IDENTIFIER_TEST_H
#define IDENTIFIER_TEST_H

#include <set>

// тесты для идентификатора
class IdentifierTest
{
public:
    IdentifierTest();

    // запуск всех тестов
    void runAllTests();

    void invalidLetterIdentifierGroupTest();
    void invalidNumberIdentifierGroupTest();
    void invalidLengthIdentifierGroupTest();
    void numberSingleIdentifierGroupTest();
    void letterSingleIdentifierGroupTest();

    void invalidLetterIdentifierTest();
    void invalidNumberIdentifierTest();
    void invalidLengthIdentifierTest();
    void numberIdentifierTest();
    void letterIdentifierTest();
    void addNewIdentifierGroupTest();
    void maxIdentifierGroupCountTest();

protected:
    bool isLetterDeprecated_(char letter) const;

    std::set<char> deprecatedLetters_;
};

#endif
