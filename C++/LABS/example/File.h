#pragma once
#include <fstream>
#include <string>
#include "OneWayQueue.h" 
class File
{
protected:
	std::string filename;
	std::ifstream ifs;
	std::ofstream ofs;
	std::fstream  fs;

public:
	File() = default;

	explicit File(const std::string& filename)
	{
		this->filename = filename;
	}

	~File()
	{
		ifs.close();
		ofs.close();
		fs.close();
	}


	void setFilename(const std::string& new_filename)
	{
		filename = new_filename;
	}

	const std::string& getFilename() const
	{
		return filename;
	}
};
