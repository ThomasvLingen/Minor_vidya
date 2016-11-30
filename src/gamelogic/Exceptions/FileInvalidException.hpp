#ifndef FILEINVALIDEXCEPTION_HPP
#define FILEINVALIDEXCEPTION_HPP

#include <iostream>
#include <exception>
namespace Exceptions {
    class FileInvalidException : public std::exception {
    public:
        virtual const char* what() const throw( );
    };
}
#endif // !FILEINVALIDEXCEPTION_HPP