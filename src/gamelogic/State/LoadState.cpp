//
// Created by sander on 11/17/16.
//

#include "LoadState.hpp"
#include "../Game.hpp"
using State::LoadState;

namespace State {

    LoadState::LoadState(){

    }

    LoadState::~LoadState(){

    }

    void LoadState::update(GameLogic::Game& game) {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        game._SDL_facade.clear_screen();
        game._SDL_facade.draw_rect(CoordinateDouble{0,0}, 640, 480, Color{0,0,0});
        timer = timer + 1; //TODO: To ticks
        Color color{255,255,255};
        game._SDL_facade.draw_text("Level Name Here", FontType::alterebro_pixel, color, CoordinateDouble{500,15});
        if(timer < 150){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_1.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Finding Files...", FontType::alterebro_pixel, color, CoordinateDouble{265,260});
        }
        else if(timer < 300){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_2.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Casting Rays...", FontType::alterebro_pixel, color, CoordinateDouble{265,260});
        }
        else if(timer < 450){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_3.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Calculating Edges...", FontType::alterebro_pixel, color, CoordinateDouble{245,260});
        }
        else if(timer < 600){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_4.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Doing other stuff...", FontType::alterebro_pixel, color, CoordinateDouble{245,260});
        }
        else if(timer < 750){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_5.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Placing Player...", FontType::alterebro_pixel, color, CoordinateDouble{260,260});
        }
        else if(timer < 900){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Increasing movement speed...", FontType::alterebro_pixel, color, CoordinateDouble{203,260});
        }
        else if(timer < 1050){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_7.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Making textures...", FontType::alterebro_pixel, color, CoordinateDouble{247,260});
        }
        else if(timer < 1200){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Destroying textures...", FontType::alterebro_pixel, color, CoordinateDouble{232,260});
        }
        else if(timer < 1350){
            game._SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, color, CoordinateDouble{255,150});
            game._SDL_facade.draw_image("res/loading_bar/loading_bar_8.bmp", CoordinateDouble{220, 220});
            game._SDL_facade.draw_text("Overloading!!!", FontType::alterebro_pixel, color, CoordinateDouble{265,260});
        }
        else if(timer < 1450){
            game._SDL_facade.draw_text("Done Loading!", FontType::alterebro_pixel_plus, color, CoordinateDouble{220,150});
        }
        else{
            timer = 0;
            game.set_new_state(game.get_run_state());
        }
        game._SDL_facade.render_buffer();

    }
}