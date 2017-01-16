//
// Created by martijn on 12/20/16.
//

#include "InvalidSoundFileException.hpp"

namespace Exceptions {
    const char * InvalidSoundFileException::what() const throw( )
    {
        return "Could not load sound file";
    }
}