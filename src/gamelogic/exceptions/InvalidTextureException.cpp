#include "InvalidTextureException.hpp"

namespace Exceptions {
    const char * InvalidTextureException::what() const throw( )
    {
        return "Tile has no texture";
    }
}