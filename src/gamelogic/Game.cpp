//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"
#include "Player.hpp"

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
        this->_init_sound_effects();
        this->init_states();

        Engine::SPTR_AssetsManager assets = std::make_shared<AssetsManager>(this->SDL_facade);
        if (!assets->init()) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        // TODO: This is test code of the worst kind, remove when no longer needed (f/e when we have a level editor)
        // {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        std::vector<std::vector<int>> world = {
            {1,1,1,1,1,7,7,7,7,7,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1},
            {1,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,7,0,0,0,0,7,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,7,0,0,0,0,7,3,3,3,3,3,3,1,0,0,8,9,10,11,12,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,7,7,7,7,7,7,3,3,3,3,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,0,0,0,3,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,4,0,1,0,0,0,3,0,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,5,0,1,0,0,0,3,0,3,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,6,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,1},
            {13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,13},
            {1,0,0,0,0,0,0,0,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
            {1,0,0,0,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,6,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        std::vector<std::vector<Tile*>> tiles;

        for(size_t i = 0; i < world.size(); i++){
            std::vector<Tile*>* vector = new std::vector<Tile*>;
            tiles.push_back(*vector);

            for(size_t j = 0; j < world.at(i).size(); j++){
                Tile* temp = new Tile(assets->get_texture(world[i][j]));

                // Only > 0 is a wall, the rest is empty
                temp->set_wall(world[i][j] > 0);

                tiles.at(i).push_back(temp);
            }
        }

        // TODO: The AssetsManager should not be newed here
        this->_level = {
            std::make_shared<Level>(
                Level(tiles, assets)
            )
        };
        this->raycasting_engine.set_world(this->_level);

        // Player start coords
        CoordinateDouble coord = {10.5,1.5};
        auto player = std::make_shared<Player>(coord, this->_level);

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

