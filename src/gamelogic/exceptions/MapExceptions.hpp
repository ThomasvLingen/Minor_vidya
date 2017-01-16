//
// Created by mafn on 1/16/17.
//

#ifndef MINOR_VIDYA_CANNOTSETMAPEXCEPTION_HPP
#define MINOR_VIDYA_CANNOTSETMAPEXCEPTION_HPP

#include <exception>

namespace Exceptions {
    class MapIsNullptrException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
}

#endif //MINOR_VIDYA_CANNOTSETMAPEXCEPTION_HPP
