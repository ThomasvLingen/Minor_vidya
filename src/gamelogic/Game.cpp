//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"
#include "Player.hpp"
#include "WorldParser.hpp"

#include "state/StartUpState.hpp"

namespace GameLogic {
    Game::Game()
    : SDL_facade([this](){ //lambda function, captures this (the game class) and sets running to false as quit callback
        this->running = false;
    })
    , raycasting_engine(this->SDL_facade)
    , running(true)
    {
        this->SDL_facade.init();
        WorldParser parser;
        this->_init_sound_effects();
        this->init_states();
        Engine::SPTR_AssetsManager assets = std::make_shared<AssetsManager>(this->SDL_facade);
        if (!assets->init()) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        this->_level = { std::make_shared<Level>(parser.generate_level("res/test2.tmx")) };
        this->_raycasting_engine.set_world(this->_level);

        auto player = std::make_shared<Player>(this->_level->get_spawnpoint(), this->_level);

        this->_level->set_player(player);
    }

    /// \brief The main game loop
    ///
    /// first handle input, thereafter update and finally clear and draw the screen.
    void Game::run()
    {
        int time_since_last_frame;
        int last_frame_start_time = this->SDL_facade.get_ticks();
        int current_frame_start_time;
        int time_spent;

        while (this->running) {
            current_frame_start_time = this->SDL_facade.get_ticks();
            time_since_last_frame = current_frame_start_time - last_frame_start_time;
            last_frame_start_time = this->SDL_facade.get_ticks();

            this->_current_state = this->_new_state;
            this->_current_state->update(time_since_last_frame);

            time_spent = this->SDL_facade.get_ticks() - current_frame_start_time;

            if (FRAME_DURATION > time_spent) { //TODO use vsync instead of this
                this->SDL_facade.delay_millis(FRAME_DURATION - time_spent);
            }
        }
    }

    void Game::set_new_state(SPTR_IGameState state)
    {
        this->_new_state = state;
    }

    void Game::init_states()
    {
        this->_new_state = std::make_shared<State::StartUpState>(*this);
    }

    void Game::_init_sound_effects() {
        this->SDL_facade.load_sound_effect("monsterkill", VIDYA_RUNPATH + "res/sound_effects/monsterkill.wav");
        this->SDL_facade.load_sound_effect("headshot", VIDYA_RUNPATH + "res/sound_effects/headshot.wav");
    }
}

