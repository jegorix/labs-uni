#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>


class Exception : public std::exception
{
    protected:
        std::string message;
        std::string fileName;
        int lineNumber;

    public:
        explicit Exception(const std::string& msg="");
        Exception(const std::string& msg, const std::string& file, int line);

        virtual ~Exception() = default;
        virtual const char* what() const noexcept override;


        virtual std::string getMessage() const;
        virtual std::string getFileName() const;
        virtual int getLineNumber() const;


        virtual std::string getType() const;
        virtual std::string getFullInfo() const;

};

#define THROW_EXCEPTION(msg) throw Exception(msg, __FILE__, __LINE__)

#endif