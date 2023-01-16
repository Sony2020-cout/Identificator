#include "Identifier.h"
#include "IdentifierTest.h"
#include <cassert>

using namespace std;

string getNextIdentifier(const string& str)
{
    Identifier identifier(str);

    identifier.increase();

    return identifier.getString();
}

int main(int argc, char* argv[])
{
    IdentifierTest test;

    test.runAllTests();

    // обычное использование
    const string str = getNextIdentifier("A1-B2-C3");

    assert(str == "A1-B2-C4");

    return 0;
}
