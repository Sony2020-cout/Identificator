#ifndef IDENTIFIER_EXCEPTIONS_H
#define IDENTIFIER_EXCEPTIONS_H

#include <stdexcept>

// исключения для работы с идентификаторами
class IdentifierException : public std::runtime_error
{
public:
	IdentifierException(const char* msg) : std::runtime_error(msg)
	{
	}
};

class InvalidIdentifierException : public IdentifierException
{
public:
	InvalidIdentifierException(const char* msg) : IdentifierException(msg)
	{
	}
};

class EndOfSequenceException : public IdentifierException
{
public:
	EndOfSequenceException() : IdentifierException("End of sequence reached!")
	{
	}
};

#endif
