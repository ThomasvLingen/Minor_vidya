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
        Menu(vector<CoordinateDouble> coordinates, vector<std::string> names, vector<std::function>& callbacks);
        ~Menu();

        void set_next();
        void set_previous();

        MenuOption* get_selected();

    private:

        void set_selected();

    };
}

#endif //MINOR_VIDYA_MENU_HPP
