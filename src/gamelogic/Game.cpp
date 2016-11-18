//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"
#include "Player.hpp"

#include "State/CreditState.hpp"
#include "State/LoadState.hpp"
#include "State/MenuState.hpp"
#include "State/PauseState.hpp"
#include "State/RunState.hpp"
#include "State/StartUpState.hpp"
#include "State/HelpState.hpp"

namespace GameLogic {
    Game::Game()
    : _running(true)
    , _SDL_facade([this](){ //lambda function, captures this (the game class) and sets running to false as quit callback
        this->_running = false;
    })
    , _raycasting_engine(this->_SDL_facade)
    {
        this->_SDL_facade.init();
        this->_pause_state = std::make_shared<State::PauseState>();
        this->_run_state = std::make_shared<State::RunState>();
        this->_load_state = std::make_shared<State::LoadState>();
        this->_credit_state = std::make_shared<State::CreditState>();
        this->_menu_state = std::make_shared<State::MenuState>();
        this->_start_up_state = std::make_shared<State::StartUpState>();
        this->_help_state = std::make_shared<State::HelpState>();
        this->_current_state = _start_up_state;

        // TODO: This is test code of the worst kind, remove when no longer needed (f/e when we have a level editor)
        std::vector<std::vector<int>> world = {
            {1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,2},
            {1,0,2,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,2},
            {1,0,3,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,2},
            {1,1,1,1,1,1,1,1,1,1,1}
        };
        std::vector<std::vector<Tile*>> tiles;

        for(size_t i = 0; i < world.size(); i++){
            std::vector<Tile*>* vector = new std::vector<Tile*>;
            tiles.push_back(*vector);


            for(size_t j = 0; j < world.at(i).size(); j++){
                Tile* temp = new Tile();

                switch (world[i][j]) {
                    case 1:
                        temp->set_wall(true);
                        temp->set_color({255,0,0});
                    break;
                    case 2:
                        temp->set_wall(true);
                        temp->set_color({0,255,0});
                    break;
                    case 3:
                        temp->set_wall(true);
                        temp->set_color({0,0,255});
                    break;
                    default:
                        temp->set_wall(false);
                }

                tiles.at(i).push_back(temp);
            }
        }

        this->_level = { std::make_shared<Level>(Level(tiles)) };
        this->_raycasting_engine.set_world(this->_level);

        CoordinateDouble coord = {1.5,1.5};
        auto player = std::make_shared<Player>(coord, this->_level);

        this->_level->set_player(player);
    }

    Game::~Game() {

    }

    /// \brief The main game loop
    ///
    /// first handle input, thereafter update and finally clear and draw the screen.
    void Game::run()
    {
        int last_frame_start_time = this->_SDL_facade.get_ticks();
        int current_frame_start_time;
        int time_spent;

        while (this->_running) {
            current_frame_start_time = this->_SDL_facade.get_ticks();
            this->_time_since_last_frame = current_frame_start_time - last_frame_start_time;
            last_frame_start_time = this->_SDL_facade.get_ticks();

            this->_current_state->update(*this);

            time_spent = this->_SDL_facade.get_ticks() - current_frame_start_time;

            if (FRAME_DURATION > time_spent) {
                this->_SDL_facade.delay_millis(FRAME_DURATION - time_spent);
            }
        }
    }

    int Game::get_time_since_last_frame()
    {
        return this->_time_since_last_frame;
    }

    void Game::set_new_state(SPTR_IGameState state)
    {
        this->_current_state = state;
    }

    SPTR_IGameState Game::get_credit_state()
    {
        return this->_credit_state;
    }

    SPTR_IGameState Game::get_load_state()
    {
        return this->_load_state;
    }

    SPTR_IGameState Game::get_menu_state()
    {
        return this->_menu_state;
    }

    SPTR_IGameState Game::get_pause_state()
    {
        return this->_pause_state;
    }

    SPTR_IGameState Game::get_run_state()
    {
        return this->_run_state;
    }

    SPTR_IGameState Game::get_start_up_state()
    {
        return this->_start_up_state;
    }
    SPTR_IGameState Game::get_help_state()
    {
        return this->_help_state;
    }
}

