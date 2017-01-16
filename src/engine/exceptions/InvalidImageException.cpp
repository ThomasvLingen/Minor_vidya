//
// Created by martijn on 12/20/16.
//

#include "InvalidImageException.hpp"

namespace Exceptions {
    const char * InvalidImageException::what() const throw( )
    {
        return "Could not load image";
    }
}