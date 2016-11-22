//
// Created by sander on 11/21/16.
//

#ifndef MINOR_VIDYA_MENUOPTION_HPP
#define MINOR_VIDYA_MENUOPTION_HPP

#include <functional>
#include "../Game.hpp"
#include "../../engine/domain/CoordinateDouble.hpp"

namespace State {

    using GameLogic::Game;
    using Engine::CoordinateInt;

    class MenuOption {

    public:
        MenuOption();
        MenuOption(CoordinateInt coordinates, std::string name, std::function<void(Game&)> callback);

        CoordinateInt coordinates;
        std::string text;
        std::function<void(Game&)> callback;

    };

}

#endif //MINOR_VIDYA_MENUOPTION_HPP
