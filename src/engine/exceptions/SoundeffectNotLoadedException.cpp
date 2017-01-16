//
// Created by martijn on 12/20/16.
//

#include "SoundeffectNotLoadedException.hpp"
namespace Exceptions {
    const char * SoundeffectNotLoadedException::what() const throw( )
    {
        return "Sound effect was not loaded";
    }
}