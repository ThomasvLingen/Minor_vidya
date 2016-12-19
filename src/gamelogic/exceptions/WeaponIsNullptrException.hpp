#ifndef MINOR_VIDYA_WEAPONISNULLPTREXCEPTION_HPP
#define MINOR_VIDYA_WEAPONISNULLPTREXCEPTION_HPP

#include <iostream>
#include <exception>

namespace Exceptions {
    class WeaponIsNullptrException : public std::exception {
    public:
        virtual const char* what() const throw( );
    };
}

#endif //MINOR_VIDYA_WEAPONISNULLPTREXCEPTION_HPP
