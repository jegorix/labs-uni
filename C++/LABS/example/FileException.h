#pragma once
#include "Exception.h"	


class FileException : public Exception
{
protected:
	std::string massage = "";

public:
	FileException() {}

	FileException(const int& code, std::string massage) : Exception(code)
	{
		this->massage = massage;
	}

	FileException(const FileException& other) : Exception(other)
	{
		massage = other.massage;
	}

	~FileException() = default;


	std::string getMessage() const
	{
		return massage;
	}


};
