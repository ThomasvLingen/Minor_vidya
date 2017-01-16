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
#include "state/HighscoreState.hpp"
#include "../config.hpp"
#include "entities/Soldier.hpp"
#include "weapons/Pistol.hpp"
#include "weapons/MachineGun.hpp"
#include "weapons/ChainGun.hpp"
#include "exceptions/MapExceptions.hpp"

namespace GameLogic {
    Game::Game()
    : SDL_facade([this](){ //lambda function, captures this (the game class) and sets running to false as quit callback
        this->running = false;
    })
    , control_mapper(ControlMapper())
    , raycasting_engine(this->SDL_facade)
    , running(true)
    , _current_map(nullptr)
    {
        this->SDL_facade.init();
        this->_init_sound_effects();
        this->init_states();
    }

    Game::~Game()
    {
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

        this->_player = std::make_shared<Player>(CoordinateDouble{0,0}, this->SDL_facade, control_mapper);
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

    HighscoreObject* Game::get_highscore_object() {
        return &this->_highscore_object;
    }

    void Game::init_states()
    {
        this->_new_state = std::make_shared<State::StartUpState>(*this);
    }

    void Game::_init_sound_effects() {
        this->SDL_facade.load_sound_effect("monsterkill", "res/sound_effects/monsterkill.wav");
        this->SDL_facade.load_sound_effect("headshot", "res/sound_effects/headshot.wav");
        this->SDL_facade.load_sound_effect("punch", "res/sound_effects/punch.wav");
        this->SDL_facade.load_sound_effect("air", "res/sound_effects/air.wav");
    }

    void Game::_init_weapons()
    {
        this->_player->give_weapon(new Pistol(this->SDL_facade));
        this->_player->give_weapon(new MachineGun(this->SDL_facade));
        this->_player->give_weapon(new ChainGun(this->SDL_facade));
    }

    SPTR_Level Game::get_level()
    {
        if (this->_level != nullptr) {
            return this->_level;
        } else {
            throw Exceptions::LevelIsNullptrException();
        }
    }

    /// \brief Sets the map that is currently being played. This is typically done upon loading it.
    ///        Setting a map when another is already being played overrides it.
    /// \param new_map New map that is going to be played
    void Game::set_current_map(CampaignMap* new_map)
    {
        this->_current_map = new_map;
    }

    /// \brief Gets the CampaignMap that's currently being played.
    /// \throws When the map is not set before calling this function, it throws a MapIsNullPtr exception
    /// \return The CampaignMap that's being played
    CampaignMap* Game::get_current_map()
    {
        if (this->_current_map != nullptr) {
            return this->_current_map;
        } else {
            throw Exceptions::MapIsNullptrException();
        }
    }

    /// \brief resets the map that's being played, this is typically done upon exiting a level, either through
    /// completion or quitting.
    void Game::reset_map()
    {
        this->set_current_map(nullptr);
    }
}

