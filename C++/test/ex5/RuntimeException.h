#ifndef RUNTIME_EXCEPTION
#define RUNTIME_EXCEPTION

#include "Exception.h"

class RuntimeException: public Exception 
{
    public:
        explicit RuntimeException(const std::string& msg = "");
        RuntimeException(const std::string& msg, const std::string& file, int line);

        std::string getType() const override;
};

#define THROW_RUNTIME_EXCEPTION(msg) throw RuntimeException(msg, __FILE__, __LINE__)


#endif