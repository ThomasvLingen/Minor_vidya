#include "WeaponIsNullptrException.hpp"

namespace Exceptions {
    const char * WeaponIsNullptrException::what() const throw( )
    {
        return "Weapon was nullptr";
    }
}