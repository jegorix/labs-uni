#pragma once

#include <string>
#include <fstream>
#include "../exceptions/include/FileException.hpp"

using namespace std;

class File
{
protected:
    string filename;
    ifstream iFile;
    ofstream oFile;
    fstream fFile;

public:
    File(const string& filename) : filename(filename) {}
    virtual ~File()
    {
        if (iFile.is_open())
        {
            iFile.close();
        }
        if (oFile.is_open())
        {
            oFile.close();
        }
        if (fFile.is_open())
        {
            fFile.close();
        }
    }
};
