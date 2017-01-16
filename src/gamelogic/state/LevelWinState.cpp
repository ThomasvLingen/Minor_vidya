//
// Created by waseland on 12/7/16.
//

#include "LevelWinState.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"
#include "../../util/UnusedMacro.hpp"
#include "../../util/StringUtil.hpp"
#include "../exceptions/MapExceptions.hpp"
#include "LoadState.hpp"

namespace State {

    LevelWinState::LevelWinState(Game& context)
    : IGameState(context)
    , _menu(this->_context.SDL_facade, this->_context)
    {
        this->_level_completed_text = "Completed ";
        this->_level_time_text = "Time taken: " + StringUtil::time_to_string(this->_context.get_level()->in_game_ticks / 1000);
        this->_context.get_highscore_object()->add_score(this->_context.get_level()->in_game_ticks / 1000, "xxxx");
        vector<MenuOption> menu_options;

        try {
            this->_completed_map = this->_context.get_current_map();
            this->_level_completed_text += this->_completed_map->name;

            try {
                CampaignMap& next_map = this->_context.campaign.get_next_level(*this->_completed_map);

                next_map.unlocked = true;

                menu_options.push_back(
                    MenuOption {
                        {250,100},
                        "Continue to next level",
                        [&next_map] (GameLogic::Game& game) {
                            game.set_new_state(std::make_shared<LoadState>(game, next_map));
                        }
                    }
                );
            } catch (Exceptions::NoNextMapExcepion e) {
                // We do nothing here, we don't unlock the next level or add the menu option for loading the next level.
                std::cout << e.what() << std::endl;
            }
        } catch (Exceptions::MapIsNullptrException e) {
            std::cout << e.what() << std::endl;
            this->_level_completed_text += "[error]";
        }

        this->_context.reset_map();

        MenuOption quit_game {
                {250,140},
                "Quit to menu",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<MenuState>(game));
                }
        };
        menu_options.push_back(quit_game);

        this->_menu.add_options(menu_options);
        this->_menu.set_escape_option(quit_game);

        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void LevelWinState::update(int time_since_last_update) {
        UNUSED(time_since_last_update);
        this->_context.SDL_facade.clear_screen();

        this->_context.SDL_facade.draw_image("res/levelwin.bmp" , {0,0});
        this->_context.SDL_facade.draw_text(this->_level_completed_text, FontType::alterebro_pixel_medium, this->_color, {225, 15});
        this->_context.SDL_facade.draw_text(this->_level_time_text, FontType::alterebro_pixel_medium, this->_color, {225, 200});

        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}