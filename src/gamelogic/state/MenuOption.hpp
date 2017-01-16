//
// Created by sander on 11/21/16.
//

#ifndef MINOR_VIDYA_MENUOPTION_HPP
#define MINOR_VIDYA_MENUOPTION_HPP

#include <functional>
#include "../Game.hpp"
#include "../../engine/domain/CoordinateDouble.hpp"
#include "../../engine/domain/Color.hpp"

namespace State {

    using GameLogic::Game;
    using Engine::CoordinateInt;
    using Engine::Color;

    class MenuOption {

    public:
        MenuOption();
        // Default text color is white
        MenuOption(CoordinateInt coordinates, std::string name, std::function<void(Game&)> callback, Color color={255, 255, 255});

        CoordinateInt coordinates;
        std::string text;
        std::function<void(Game&)> callback;
        Color color;
    };

}

#endif //MINOR_VIDYA_MENUOPTION_HPP
