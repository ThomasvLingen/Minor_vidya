//
// Created by mafn on 1/16/17.
//

#include "MapExceptions.hpp"

namespace Exceptions {
    const char* MapIsNullptrException::what() const throw()
    {
        return "map is a nullptr, which means it wasn't set";
    }
}