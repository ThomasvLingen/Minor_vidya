//
// Created by sander on 1/16/17.
//

#include "HighscoreState.hpp"
#include "../../util/StringUtil.hpp"

namespace State {
    HighscoreState::HighscoreState(Game &context)
    : IGameState(context)
    {

    }

    void HighscoreState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        for (auto key : keys.keys_released) {
            switch (key) {
                case Key::ESC:
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/highscorescreen.bmp" , CoordinateInt{0,0});

        this->_context.SDL_facade.draw_text("Highscores:", this->_font, this->_color, {150, 40});
        map<string, vector<highscore>> scores = _context.get_highscore_object()->get_all_scores();

        int level_name_x = this->_start_pos_x_names;
        int level_score_x = this->_start_pos_x_scores;

        for(auto string_highscore_pair : scores){
            // for each highscore level

            int highscore_y = this->_start_pos_y;
            this->_context.SDL_facade.draw_text(string_highscore_pair.first, this->_font, this->_color,
                                                {level_name_x, highscore_y - 30});

            for(int i = 0; i < string_highscore_pair.second.size(); i++){
               //for each time per level
                this->_context.SDL_facade.draw_text(to_string(i + 1) + ". ", this->_font, this->_color,
                                                    {level_name_x, highscore_y});

                this->_context.SDL_facade.draw_text(StringUtil::time_to_string(string_highscore_pair.second[i].score), this->_font,
                                                    this->_color, {level_score_x, highscore_y});

                highscore_y += this->_step_size_y;
            }

            level_name_x += this->_step_size_x;
            level_score_x += this->_step_size_x;
        }

        this->_context.SDL_facade.render_buffer();
    }
}