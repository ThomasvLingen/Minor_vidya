//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"
#include "Player.hpp"
#include "WorldParser.hpp"
#include "../engine/PathUtil.hpp"
#include "exceptions/FileInvalidException.hpp"

#include "state/StartUpState.hpp"
#include "../config.hpp"

namespace GameLogic {
    Game::Game()
    : SDL_facade([this](){ //lambda function, captures this (the game class) and sets running to false as quit callback
        this->running = false;
    })
    , raycasting_engine(this->SDL_facade)
    , running(true)
    {
        this->SDL_facade.init();
        this->_init_sound_effects();
        this->init_states();
    }

    /// \brief The main game loop
    ///
    /// first handle input, thereafter update and finally clear and draw the screen.
    void Game::run()
    {
        int time_since_last_frame;
        int last_frame_start_time = this->SDL_facade.get_ticks();
        int current_frame_start_time;

        while (this->running) {
            current_frame_start_time = this->SDL_facade.get_ticks();
            time_since_last_frame = current_frame_start_time - last_frame_start_time;
            last_frame_start_time = this->SDL_facade.get_ticks();

            this->_current_state = this->_new_state;
            this->_current_state->update(time_since_last_frame);

            // We only have to wait if VSync is disabled. Otherwise it's done for us.
            if (!Config::USE_VSYNC) {
                int time_spent = this->SDL_facade.get_ticks() - current_frame_start_time;

                if (FRAME_DURATION > time_spent) { //TODO use vsync instead of this
                    this->SDL_facade.delay_millis(FRAME_DURATION - time_spent);
                }
            }
        }
    }

    void Game::set_new_state(SPTR_IGameState state)
    {
        this->_new_state = state;
    }

    /// \brief Load a level
    ///
    /// Loads a level based on the file_location
    ///
    /// \param file_location location of the level.tmx to be loaded 
    bool Game::load_Level(std::string file_location)
    {
        WorldParser parser;
        Engine::SPTR_AssetsManager assets = std::make_shared<AssetsManager>( this->SDL_facade );

        this->_player = std::make_shared<Player>(CoordinateDouble{0,0});
        this->_level = { std::make_shared<Level>(*this->_player, assets) };

        try {
            parser.fill_level(*this->_level, file_location);
        }
        catch ( const Exceptions::FileInvalidException& e ) {
            std::cout << e.what() << std::endl;
            std::cout << "Returning to Menu" << std::endl;
            return false;
        }
        catch ( const std::exception& e ) {
            std::cout << e.what() << std::endl;
            std::cout << "Returning to Menu" << std::endl;
            return false;
        }

        this->_player->set_level(this->_level);
        this->raycasting_engine.set_world( this->_level );
        // TODO: THIS IS TEMPORARY TESTING CODE
        this->raycasting_engine.test_enemies = {
            {new Engine::Enemy(12.0, 10.0, this->_level->assets->get_texture(29))},
            {new Engine::Enemy(7.2, 4.3, this->_level->assets->get_texture(29))},
            {new Engine::Enemy(14.5, 10.0, this->_level->assets->get_texture(29))},
            {new Engine::Enemy(12.0, 8.0, this->_level->assets->get_texture(29))}
        };
        // END TODO

        return true;
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

