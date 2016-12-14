//
// Created by sander on 11/21/16.
//

#include "Menu.hpp"
#include "StartUpState.hpp"

namespace State {

    Menu::Menu(SDLFacade& SDL_facade, Game& context)
    : Drawable(SDL_facade)
    , _context(context)
    {
    }

    Menu::Menu(vector<MenuOption> options, SDLFacade& SDL_facade, Game& context)
    : Drawable(SDL_facade)
    , _menu_options(options)
    , _context(context)
    {
    }

    void Menu::set_selected(int index)
    {
        this->_selected_index = index;
    }

    void Menu::add_option(MenuOption option)
    {
        this->_menu_options.push_back(option);
    }

    MenuOption* Menu::get_selected()
    {
        return &(this->_menu_options.at((size_t)_selected_index));//todo check if exist? why use at if you check
    }

    void Menu::set_previous()
    {
        if (_selected_index > 0) {
            this->_selected_index--;
        }
        else {
            this->_selected_index = (int)this->_menu_options.size() - 1;
        }
    }

    void Menu::set_next()
    {
        if (_selected_index < (int)_menu_options.size() - 1) {
            this->_selected_index++;
        }
        else {
            this->_selected_index = 0;
        }
    }

    void Menu::add_options(vector<MenuOption> options)
    {
        this->_menu_options.insert( //append options to _menu_options
            this->_menu_options.end(),
            options.begin(),
            options.end()
        );
    }

    void Menu::draw()
    {
        for (MenuOption menu_option : this->_menu_options) {
            this->_SDL_facade.draw_text(
                menu_option.text,
                this->_font,
                this->_color,
                menu_option.coordinates
            );
        }

        this->_context.SDL_facade.draw_rect(
            {this->get_selected()->coordinates.x - this->_selected_rect_diff_width, this->get_selected()->coordinates.y + this->_selected_rect_diff_height},
            15,
            15,
            this->_color
        );
    }

    void Menu::handle_input(Input& keys)
    {
        this->_context.control_mapper->handle_input(keys);
        InputActions* input_actions = this->_context.control_mapper->get_input_actions();
        for (auto action : input_actions->actions_off) {
            switch (action) {
                //case Key::W :
                case Action::MENU_UP :
                    this->set_previous();
                    break;
                //case Key::S :
                case Action::MENU_DOWN :
                    this->set_next();
                    break;
                case Action::MENU_BACK:
                    this->_escape_option.callback(this->_context);
                    break;
                case Action::MENU_SELECT:
                    this->get_selected()->callback(this->_context);
                    break;
                default:
                    break;
            }
        }
    }

    void Menu::set_escape_option(MenuOption option)
    {
        this->_escape_option = option;
    }

    void Menu::clear_options()
    {
        this->_menu_options.clear();
    }
}
