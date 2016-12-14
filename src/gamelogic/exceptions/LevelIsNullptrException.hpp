#ifndef MINOR_VIDYA_LEVELISNULLPTREXCEPTION_HPP
#define MINOR_VIDYA_LEVELISNULLPTREXCEPTION_HPP

#include <iostream>
#include <exception>
namespace Exceptions {
    class LevelIsNullptrException : public std::exception {
    public:
        virtual const char* what() const throw( );
    };
}

#endif //MINOR_VIDYA_LEVELISNULLPTREXCEPTION_HPP
