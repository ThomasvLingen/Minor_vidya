//
// Created by mafn on 12/20/16.
//

#ifndef MINOR_VIDYA_ANIMATEDSPRITEINVALIDEXCEPTION_HPP
#define MINOR_VIDYA_ANIMATEDSPRITEINVALIDEXCEPTION_HPP

#include <exception>

namespace Exceptions {
    class AnimatedSpriteInvalidException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
}


#endif //MINOR_VIDYA_ANIMATEDSPRITEINVALIDEXCEPTION_HPP
