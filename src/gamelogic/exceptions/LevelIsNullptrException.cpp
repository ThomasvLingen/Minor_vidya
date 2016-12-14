#include "LevelIsNullptrException.hpp"

namespace Exceptions {
    const char * LevelIsNullptrException::what() const throw( )
    {
        return "Game._level was a nullptr";
    }
}