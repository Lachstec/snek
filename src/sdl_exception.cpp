#include "sdl_exception.hpp"

SdlException::SdlException(const char* message)
    : m_Message(message)
{

}

const char* SdlException::what() const throw() {
    return m_Message;
}

