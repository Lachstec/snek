#ifndef SDL_EXCEPTION
#define SDL_EXCEPTION
#include <exception>

class SdlException : std::exception  {
    public:
        SdlException(const char *message);
        const char* what() const throw();
    private:
        const char* m_Message;
};

#endif