#pragma once
#include <exception>

class SdlException : std::exception  {
    public:
        SdlException(const char *message);
        const char* what() const throw();
    private:
        const char* m_Message;
};