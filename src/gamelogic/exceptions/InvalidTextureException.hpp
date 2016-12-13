#ifndef MINOR_VIDYA_INVALIDTEXTUREEXCEPTION_HPP
#define MINOR_VIDYA_INVALIDTEXTUREEXCEPTION_HPP

#include <iostream>
#include <exception>
namespace Exceptions {
    class InvalidTextureException : public std::exception {
    public:
        virtual const char* what() const throw( );
    };
}


#endif //MINOR_VIDYA_INVALIDTEXTUREEXCEPTION_HPP
