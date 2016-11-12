//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"


namespace GameLogic {
    Game::Game()
    : _running(true)
    , _SDL_facade([this](){ //lamba function, captures this (the game class) and sets running to false as quit callback
        this->_running = false;
    })
    , _raycasting_engine(this->_SDL_facade)
    {
        this->_SDL_facade.init();
    }

    void Game::run()
    {
        int time_since_last_frame;
        int last_frame_start_time = this->_SDL_facade.get_ticks();
        int current_frame_start_time;
        int time_spent;

        while (this->_running) {
            current_frame_start_time = this->_SDL_facade.get_ticks();
            time_since_last_frame = current_frame_start_time - last_frame_start_time;
            last_frame_start_time = this->_SDL_facade.get_ticks();

            this->_SDL_facade.handle_sdl_events();
            this->_raycasting_engine.update(time_since_last_frame);
            this->_SDL_facade.clear_screen();

            this->_raycasting_engine.draw();

            this->_SDL_facade.draw_text("Hi there", Engine::FontType::alterebro_pixel, Engine::Color {255, 0,0}, {50,50});
            this->_SDL_facade.draw_text("Welcome to gaem", Engine::FontType::alterebro_pixel, Engine::Color {255, 0,0}, {50,80});
            //TODO: remove once game actually draws something

            this->_SDL_facade.render_buffer();

            time_spent = this->_SDL_facade.get_ticks() - current_frame_start_time;

            if (FRAME_DURATION > time_spent) {
                this->_SDL_facade.delay_millis(FRAME_DURATION - time_spent);
            }
        }
    }
}

