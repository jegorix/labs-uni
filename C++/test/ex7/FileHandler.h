#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

class FileHandler
{
    protected:
        std::string filename;
        std::string filepath;

    public:
        FileHandler(const std::string& filename);
        virtual ~FileHandler() = default;

        virtual bool write(const std::vector<std::string>& data) = 0;
        virtual std::vector<std::string> read() = 0;
        virtual bool append(const std::vector<std::string>& data);
        
        virtual bool exists() const;
        virtual bool createEmpty();
        virtual bool deleteFile();
        virtual std::string getFullPath() const;
        virtual size_t getFileSize() const;

        std::string getFilename() { return filename; }
        std::string getFilepath() { return filepath; }

        void setFilepath(const std::string& path) {filepath = path;}
};



#endif