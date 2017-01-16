//
// Created by sander on 1/16/17.
//

#include "HighscoreState.hpp"

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
        this->_context.SDL_facade.draw_image("res/helpscreen.bmp" , CoordinateInt{0,0});

        int current_y_pos = this->_start_pos_y;
        this->_context.SDL_facade.draw_text("Highscores:", this->_font, this->_color, {150, 50});
        vector<highscore> scores = _context.get_highscore_object()->get_scores();
        for (int i = 0; i < scores.size(); i++) {
            this->_context.SDL_facade.draw_text(scores[i].name, this->_font, this->_color, {this->_start_pos_x_names, current_y_pos});
            this->_context.SDL_facade.draw_text(to_string(scores[i].score), this->_font, this->_color, {this->_start_pos_x_scores, current_y_pos});
            current_y_pos += this->_step_size_y;
        }

        this->_context.SDL_facade.render_buffer();
    }
}