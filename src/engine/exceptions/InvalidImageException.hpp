//
// Created by martijn on 12/20/16.
//

#ifndef MINOR_VIDYA_INVALIDIMAGEEXCEPTION_HPP
#define MINOR_VIDYA_INVALIDIMAGEEXCEPTION_HPP

#include <iostream>
#include <exception>

namespace Exceptions {
    class InvalidImageException : public std::exception {
        public:
        virtual const char* what() const throw( );
    };
}


#endif //MINOR_VIDYA_INVALIDIMAGEEXCEPTION_HPP
