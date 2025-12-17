#pragma once
#include "Exception.h"	


class OneWayQueueException : public Exception
{
protected:
	std::string massage = "";

public:
	OneWayQueueException() {}

	OneWayQueueException(const int& code, std::string massage) : Exception(code)
	{
		this->massage = massage;
	}

	OneWayQueueException(const OneWayQueueException& other) : Exception(other)
	{
		massage = other.massage;
	}

	~OneWayQueueException() = default;


	std::string getMessage() const
	{
		return massage;
	}

};
