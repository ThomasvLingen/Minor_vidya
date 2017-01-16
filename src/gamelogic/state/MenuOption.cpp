//
// Created by sander on 11/21/16.
//

#include "MenuOption.hpp"

namespace State {

    MenuOption::MenuOption()
    {
        // TODO: This constructor exists for bad reasons
    }

    MenuOption::MenuOption(CoordinateInt coordinates, std::string name, std::function<void(Game&)> callback, Color color)
    : coordinates(coordinates)
    , text(name)
    , callback(callback)
    , color(color)
    {

    }
}


