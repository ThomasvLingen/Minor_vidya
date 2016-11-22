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
#include "../../engine/interface/Drawable.hpp"
#include "../../engine/interface/Handleable.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/domain/Color.hpp"

namespace State {

    using Engine::CoordinateDouble;
    using std::vector;
    using Engine::Drawable;
    using Engine::SDLFacade;
    using Engine::Handleable;
    using Engine::Key;
    using Engine::FontType;
    using Engine::Color;

    class Menu : public Drawable, public Handleable {

    public:
        Menu(vector<MenuOption> options, SDLFacade& SDL_facade, Game& context);
        Menu(SDLFacade& SDL_facade, Game& context);

        void set_next();

        virtual void draw() override;
        virtual void handle_input(::Engine::PressedKeys& keys) override;

        void set_previous();
        void add_option(MenuOption option);
        void add_options(vector<MenuOption> options);
        MenuOption* get_selected(); //TODO: Change this to smart-pointer??

        void set_selected(int index);

    private:
        vector<MenuOption> _menu_options;
        int _selected_index = 0;
        const FontType _font = FontType::alterebro_pixel;
        const Color _color = {255,255,255};
        Game& _context;

        int _time_since_last_press = 0;
    };
}

#endif //MINOR_VIDYA_MENU_HPP
