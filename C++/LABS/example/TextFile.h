#pragma once
#include "File.h"
#include "FileException.h"

template<typename T>
class TextFile : public File
{
public:
	explicit TextFile(const std::string& filename) : File(filename) {}

	void openForWrite();
	void openForRead();
	void write(const T& obj);
	T read();
	bool eof() const;

};


#include "TextFile.hpp"
