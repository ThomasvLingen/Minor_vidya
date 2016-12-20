//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"
#include "Player.hpp"
#include "WorldParser.hpp"
#include "../engine/PathUtil.hpp"
#include "exceptions/FileInvalidException.hpp"
#include "exceptions/LevelIsNullptrException.hpp"

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
                const int frame_duration = 1000 / Config::FPS;
                int time_spent = this->SDL_facade.get_ticks() - current_frame_start_time;

                if (frame_duration > time_spent) { //TODO use vsync instead of this
                    this->SDL_facade.delay_millis(frame_duration - time_spent);
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
        this->_init_weapons();
        this->raycasting_engine.set_world( this->_level );

        return true;
    }

    void Game::init_states()
    {
        this->_new_state = std::make_shared<State::StartUpState>(*this);
    }

    void Game::_init_sound_effects() {
        this->SDL_facade.load_sound_effect("monsterkill", "res/sound_effects/monsterkill.wav");
        this->SDL_facade.load_sound_effect("headshot", "res/sound_effects/headshot.wav");
        this->SDL_facade.load_sound_effect("pistolshot", "res/sound_effects/pistolshot.wav");
        this->SDL_facade.load_sound_effect("machinegunshot", "res/sound_effects/machinegunshot.wav");
        this->SDL_facade.load_sound_effect("chaingunshot", "res/sound_effects/chaingunshot.wav");
    }

    void Game::_init_weapons()
    {
        //pistol
        vector<string> pistol_images = {
                "res/gun/pistol1.bmp",
                "res/gun/pistol2.bmp",
                "res/gun/pistol3.bmp",
                "res/gun/pistol4.bmp",
                "res/gun/pistol5.bmp"
        };

        this->_player->give_weapon(new Weapon(this->SDL_facade, {120,26}, 1, "pistolshot", 150, pistol_images, 1, 10));
        //machine gun
        vector<string> machinegun_images = {
                "res/gun/machine_gun1.bmp",
                "res/gun/machine_gun2.bmp",
                "res/gun/machine_gun3.bmp",
                "res/gun/machine_gun4.bmp",
                "res/gun/machine_gun5.bmp",
                "res/gun/machine_gun6.bmp",
                "res/gun/machine_gun7.bmp",
                "res/gun/machine_gun8.bmp",
                "res/gun/machine_gun9.bmp",
                "res/gun/machine_gun10.bmp",
                "res/gun/machine_gun11.bmp",
                "res/gun/machine_gun12.bmp",
                "res/gun/machine_gun13.bmp"
        };
        this->_player->give_weapon(new Weapon(this->SDL_facade, {120,26}, 1, "machinegunshot", 75, machinegun_images, 5, 3));
        //chain gun
        vector<string> chaingun_images = {
                "res/gun/chain_gun1.bmp",
                "res/gun/chain_gun2.bmp",
                "res/gun/chain_gun3.bmp",
                "res/gun/chain_gun4.bmp",
                "res/gun/chain_gun5.bmp",
                "res/gun/chain_gun6.bmp",
                "res/gun/chain_gun7.bmp",
                "res/gun/chain_gun8.bmp",
                "res/gun/chain_gun9.bmp",
                "res/gun/chain_gun10.bmp",
                "res/gun/chain_gun11.bmp",
                "res/gun/chain_gun12.bmp",
                "res/gun/chain_gun13.bmp",
                "res/gun/chain_gun14.bmp"
        };
        this->_player->give_weapon(new Weapon(this->SDL_facade, {120,26}, 1, "chaingunshot", 70, chaingun_images, 8, 2));
    }

    SPTR_Level Game::get_level() {
        if (this->_level != nullptr) {
            return this->_level;
        } else {
            throw Exceptions::LevelIsNullptrException();
        }
    }
}

