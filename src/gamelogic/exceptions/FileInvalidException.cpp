#include "FileInvalidException.hpp"


namespace Exceptions {
    const char * FileInvalidException::what() const throw( )
    {
        return "File invalid";
    }
}