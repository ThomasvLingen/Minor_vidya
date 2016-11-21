//
// Created by sander on 11/21/16.
//

#ifndef MINOR_VIDYA_MENU_HPP
#define MINOR_VIDYA_MENU_HPP

#include "../../engine/domain/CoordinateDouble.hpp"
#include "MenuOption.hpp"
#include <vector>
#include <string>
#include <functional>

namespace State {

    using Engine::CoordinateDouble;

    using std::vector;

    class Menu {

    public:
        Menu(vector<CoordinateDouble> coordinates, vector<std::string> names, vector<std::function<void(GameLogic::Game&)>>& callbacks);
        ~Menu();

        void set_next();
        void set_previous();

        MenuOption* get_selected(); //TODO: Change this to smart-pointer??

        vector<MenuOption*> menu_options;

        void set_selected(int i);

    private:
        int _selected_index = 0;

    };
}

#endif //MINOR_VIDYA_MENU_HPP
