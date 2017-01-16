//
// Created by martijn on 12/20/16.
//

#include "InvalidWavFileException.hpp"
namespace Exceptions {
    const char * InvalidWavFileException::what() const throw( )
    {
        return "Could not load WAV file";
    }
}