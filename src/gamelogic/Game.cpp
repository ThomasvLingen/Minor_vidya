//
// Created by jazula on 11/9/16.
//

#include "Game.hpp"


namespace GameLogic {
    Game::Game()
    : _running(true)
    , _SDL_facade([this](){ //lambda function, captures this (the game class) and sets running to false as quit callback
        this->_running = false;
    })
    , _raycasting_engine(this->_SDL_facade)
    {
        this->_SDL_facade.init();
        std::vector<std::vector<int>> world = {
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}
        };
        std::vector<std::vector<Tile*>> tiles;

        for(int i = 0; i < world.size(); i++){
            std::vector<Tile*>* vector = new std::vector<Tile*>;
            tiles.push_back(*vector);


            for(int j = 0; j < world.at(i).size(); j++){
                Tile* temp = new Tile();
                temp->set_wall((bool)world[i][j]);
                temp->set_color({50+50*j,0,0});
                tiles.at(i).push_back(temp);
            }
        }

        this->_level = { std::make_shared<Level>(Level(tiles)) };
        this->_raycasting_engine.set_world(this->_level);

        Player* player = new Player({1.5,1.5}, *(this->_level));
        this->_level->set_player(player);
    }

    /// \brief The main game loop
    ///
    /// first handle input, thereafter update and finally clear and draw the screen.
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
            this->_raycasting_engine.handle_input();
            this->_raycasting_engine.update(time_since_last_frame);
            this->_SDL_facade.clear_screen();

            this->_raycasting_engine.draw();

//            this->_SDL_facade.draw_text("Hi there", Engine::FontType::alterebro_pixel, Engine::Color {255, 0,0}, {50,50});
//            this->_SDL_facade.draw_text("Welcome to gaem", Engine::FontType::alterebro_pixel, Engine::Color {255, 0,0}, {50,80});
            //TODO: remove once game actually draws something

            this->_SDL_facade.render_buffer();

            time_spent = this->_SDL_facade.get_ticks() - current_frame_start_time;

            if (FRAME_DURATION > time_spent) {
                this->_SDL_facade.delay_millis(FRAME_DURATION - time_spent);
            }
        }
    }
}

