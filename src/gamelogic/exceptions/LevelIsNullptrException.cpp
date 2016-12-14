#include "LevelIsNullptrException.hpp"

namespace Exceptions {
    const char * LevelIsNullptrException::what() const throw( )
    {
        return "Level was a nullptr";
    }
}