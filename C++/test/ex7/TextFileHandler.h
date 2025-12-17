#ifndef TEXTFILEHANDLER_H
#define TEXTFILEHANDLER_H
#include "FileHandler.h"
#include <string.h>
#include <vector>

class TextFileHandler: public FileHandler
{
    private:
        std::string encoding;

    public:
        TextFileHandler(const std::string& filename, const std::string& encoding = "UTF-8");

        bool write(const std::vector<std::string>& data) override;
        std::vector<std::string> read() override;
        bool append(const std::vector<std::string>& data) override;

        bool writeLine(const std::string& line);
        std::string readLine(int lineNumber);
        bool findAndReplace(const std::string& findStr, const std::string& replaceStr);

        std::string getEncoding() const {return encoding;}
        void setEncoding(const std::string& enc) {encoding = enc;}
};


#endif