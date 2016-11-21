//
// Created by sander on 11/21/16.
//

#include "Menu.hpp"

namespace State {

    Menu::Menu(vector<CoordinateDouble> coordinates, vector<std::string> names, vector<std::function<void(GameLogic::Game&)>>& callbacks)
    {
        for(int x = 0; x < (int)callbacks.size(); x++){
            menu_options.push_back(new MenuOption(coordinates.at(x), names.at(x), callbacks.at(x)));
        }
    }

    Menu::~Menu()
    {
        for(auto option : this->menu_options){
            delete option;
        }
    }

    void Menu::set_selected(int i) {
        this->_selected_index = i;
    }

    MenuOption* Menu::get_selected(){
        return this->menu_options.at(_selected_index);
    }

    void Menu::set_previous() {
        if(!(_selected_index <= 0)){
            this->_selected_index--;
        }
    }

    void Menu::set_next() {
        if(!(_selected_index >= (int)menu_options.size() - 1)){
            this->_selected_index++;
        }

    }




}