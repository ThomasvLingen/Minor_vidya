//
// Created by mafn on 12/20/16.
//

#include "AnimatedSpriteInvalidException.hpp"

namespace Exceptions {
    const char* AnimatedSpriteInvalidException::what() const throw()
    {
        return "Parameters passed to AnimatedSprite are invalid";
    }
}