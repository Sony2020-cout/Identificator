#include "IdentifierTest.h"
#include "Identifier.h"
#include "IdentifierExceptions.h"
#include <sstream>
#include <cassert>

using namespace std;

IdentifierTest::IdentifierTest()
{
    deprecatedLetters_.insert('D');
    deprecatedLetters_.insert('F');
    deprecatedLetters_.insert('G');
    deprecatedLetters_.insert('J');
    deprecatedLetters_.insert('M');
    deprecatedLetters_.insert('Q');
    deprecatedLetters_.insert('V');
}

void IdentifierTest::runAllTests()
{
    try
    {
        invalidLetterIdentifierGroupTest();
        invalidNumberIdentifierGroupTest();
        invalidLengthIdentifierGroupTest();
        numberSingleIdentifierGroupTest();
        letterSingleIdentifierGroupTest();

        invalidLetterIdentifierTest();
        invalidNumberIdentifierTest();
        invalidLengthIdentifierTest();
        numberIdentifierTest();
        letterIdentifierTest();
        addNewIdentifierGroupTest();
        maxIdentifierGroupCountTest();
    }
    catch(IdentifierException&)
    {
        assert(!"Unhandled identifier exception arised!");
    }
    catch(...)
    {
        assert(!"Unknown exception arised!");
    }
}

void IdentifierTest::invalidLetterIdentifierGroupTest()
{
    try
    {
        IdentifierGroup identifierGroup("a1");

        assert(!"Invalid letter identifier group test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::invalidNumberIdentifierGroupTest()
{
    try
    {
        IdentifierGroup identifierGroup("B0");

        assert(!"Invalid number identifier group test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::invalidLengthIdentifierGroupTest()
{
    try
    {
        IdentifierGroup identifierGroup("A");

        assert(!"Invalid length identifier group failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }

    try
    {
        IdentifierGroup identifierGroup("A11");

        assert(!"Invalid length identifier group failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::numberSingleIdentifierGroupTest()
{
    IdentifierGroup identifierGroup("A1");

    assert(identifierGroup.getString() == "A1");

    for(int i = 2; 9 >= i; ++i)
    {
        ostringstream os;

        identifierGroup.increase();

        os << 'A' << i;

        assert(identifierGroup.getString() == os.str());
    }

    assert(identifierGroup.getString() == "A9");

    identifierGroup.increase();

    assert(identifierGroup.getString() == "B1");
}

void IdentifierTest::letterSingleIdentifierGroupTest()
{
    for(char i = 'A'; 'Z' >= i; ++i)
    {
        ostringstream os;

        os << i << '9';

        try
        {
            IdentifierGroup identifierGroup(os.str());

            identifierGroup.increase();

            const string& str = identifierGroup.getString();

            assert(!isLetterDeprecated_(i));
            assert('1' == str[1]);
        }
        catch(InvalidIdentifierException&)
        {
            assert(isLetterDeprecated_(i));
        }
    }

    IdentifierGroup identifierGroup("Z9");

    assert(identifierGroup.getString() == "Z9");

    identifierGroup.increase();

    assert(identifierGroup.getString() == "A1");
}

void IdentifierTest::invalidLetterIdentifierTest()
{
    try
    {
        Identifier identifier("a1");

        assert(!"Invalid letter identifier test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::invalidNumberIdentifierTest()
{
    try
    {
        Identifier identifier("A0");

        assert(!"Invalid number identifier test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::invalidLengthIdentifierTest()
{
    try
    {
        Identifier identifier("A");

        assert(!"Invalid length identifier test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }

    try
    {
        Identifier identifier("A11");

        assert(!"Invalid length identifier test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }

    try
    {
        Identifier identifier("A1-A1-A1-A1-A1-A1-A1-A1-A1-A1-A1"); // 11 groups

        assert(!"Invalid length identifier test failed!");
    }
    catch(InvalidIdentifierException&)
    {
    }
}

void IdentifierTest::numberIdentifierTest()
{
  Identifier identifier("A1");

  assert(identifier.getString() == "A1");

  for(int i = 2; 9 >= i; ++i)
  {
      ostringstream os;

      identifier.increase();

      os << 'A' << i;

      assert(identifier.getString() == os.str());
  }

  assert(identifier.getString() == "A9");

  identifier.increase();

  assert(identifier.getString() == "B1");
}

void IdentifierTest::letterIdentifierTest()
{
  for(char i = 'A'; 'Z' >= i; ++i)
  {
      ostringstream os;

      os << i << '9';

      try
      {
          Identifier identifier(os.str());

          identifier.increase();

          const string& str = identifier.getString();

          assert(!isLetterDeprecated_(i));
          assert('1' == str[1]);
      }
      catch(InvalidIdentifierException&)
      {
          assert(isLetterDeprecated_(i));
      }
  }
}

void IdentifierTest::addNewIdentifierGroupTest()
{
    {
        Identifier identifier("Z9");

        identifier.increase();

        assert(identifier.getString() == "A1-A1");
    }

    {
        Identifier identifier("A1-Z9");

        identifier.increase();

        assert(identifier.getString() == "A2-A1");
    }

    {
        Identifier identifier("A1-B1-Z9");

        identifier.increase();

        assert(identifier.getString() == "A1-B2-A1");
    }

    {
        Identifier identifier("A1-Z9-Z9");

        identifier.increase();

        assert(identifier.getString() == "A2-A1-A1");
    }

    {
        Identifier identifier("Z9-Z9");

        identifier.increase();

        assert(identifier.getString() == "A1-A1-A1");
    }

    {
        Identifier identifier("Z9-Z9-Z9");

        identifier.increase();

        assert(identifier.getString() == "A1-A1-A1-A1");
    }
}

void IdentifierTest::maxIdentifierGroupCountTest()
{
    try
    {
        Identifier identifier("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z8");

        identifier.increase();

        assert(identifier.getString() == "Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9");

        identifier.increase();

        assert(!"Max identifier group count test failed!");
    }
    catch(EndOfSequenceException&)
    {
    }
}

bool IdentifierTest::isLetterDeprecated_(const char letter) const
{
    return deprecatedLetters_.end() != deprecatedLetters_.find(letter);
}
