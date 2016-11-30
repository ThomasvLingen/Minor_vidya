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
    }

    void Menu::set_next()
    {
        if (_selected_index < (int)_menu_options.size() - 1) {
            this->_selected_index++;
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
            CoordinateDouble{(double)120, (double)this->get_selected()->coordinates.y + 6}, //todo delete this magic number
            15,
            15,
            _color
        );
    }

    void Menu::handle_input(::Engine::PressedKeys& keys)
    {
        if(this->_time_since_last_press < 20){ //todo this is not nice
            this->_time_since_last_press++;
        } else {
            for (auto key : keys) {
                switch (key) {
                    case Key::W :
                        this->set_previous();
                        break;
                    case Key::S :
                        this->set_next();
                        break;
                    case Key::ESC:
                        this->_escape_option.callback(this->_context);
                        break;
                    case Key::ENTER:
                        this->get_selected()->callback(this->_context);
                        break;
                    default:
                        break;
                }
                this->_time_since_last_press = 0;
            }
        }
    }

    void Menu::set_escape_option(MenuOption option)
    {
        this->_escape_option = option;
    }
}