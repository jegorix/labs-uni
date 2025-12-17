#pragma once
#include <iostream>
#include <cstdlib>	


class Exception
{
protected:
	int code = 0;

public:
	Exception() {}

	Exception(const int& code)
	{
		this->code = code;
	}

	Exception(const Exception& other)
	{
		code = other.code;
	}

	virtual ~Exception() = default;


	int getCode() const
	{
		return code;
	}

};
