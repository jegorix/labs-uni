#pragma once
#include "Exception.h"	


class InputException : public Exception
{
protected:
	std::string massage = "";

public:
	InputException() {}

	InputException(const int& code, std::string massage) : Exception(code)
	{
		this->massage = massage;
	}

	InputException(const InputException& other) : Exception(other)
	{
		massage = other.massage;
	}

	~InputException() = default;


	std::string getMessage() const
	{
		return massage;
	}

};
