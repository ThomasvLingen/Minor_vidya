//
// Created by mafn on 1/3/17.
//

#include "LevelSelectState.hpp"
#include "MenuState.hpp"
#include "LoadState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    LevelSelectState::LevelSelectState(Game& context)
    : IGameState(context)
    , _menu(context.SDL_facade, context)
    {
        this->_init_menu();

        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void LevelSelectState::update(int time_since_last_update)
    {
        UNUSED(time_since_last_update);

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_rect({0,0}, this->_context.SDL_facade.get_width(), this->_context.SDL_facade.get_height(),{0,0,0});
        this->_context.SDL_facade.handle_sdl_events();

        this->_context.SDL_facade.draw_text("Select a level", FontType::alterebro_pixel_plus, this->_title_text_color, {50, 15});

        Input keys = this->_context.SDL_facade.get_input();
        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }

    void LevelSelectState::_init_menu()
    {
        MenuOption back_to_menu = {
            {150,440},
            "Back to menu",
            [] (GameLogic::Game& game) {
                game.set_new_state(std::make_shared<MenuState>(game));
            }
        };

        int x = 150;
        int y = 70;
        const int row_height = 30;

        for (GameLogic::CampaignMap& map : this->_context.campaign.get_levels()) {
            MenuOption map_option = {
                {x, y},
                map.name,
                [&map] (GameLogic::Game& gaem) {
                    gaem.set_new_state(std::make_shared<LoadState>(gaem, map));
                }
            };

            this->_menu.add_option(map_option);
            y += row_height;
        }

        this->_menu.add_option(back_to_menu);
        this->_menu.set_escape_option(back_to_menu);
    }
}