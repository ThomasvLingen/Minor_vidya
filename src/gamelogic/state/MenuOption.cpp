//
// Created by sander on 11/21/16.
//

#include "MenuOption.hpp"

namespace State {

    MenuOption::MenuOption()
    {
        // TODO: This constructor exists for bad reasons
    }

    MenuOption::MenuOption(CoordinateDouble coordinates, std::string name, std::function<void(Game&)> callback)
    : coordinates(coordinates)
    , text(name)
    , callback(callback)
    {

    }
}


