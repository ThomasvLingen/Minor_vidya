//
// Created by sander on 11/17/16.
//

#include "StartUpState.hpp"
#include "MenuState.hpp"

namespace State {

    StartUpState::StartUpState(Game& context)
    : IGameState(context)
    {
        //test music
        context.SDL_facade.play_music("res/music/startup.mp3");

//        //test sound effect:
//        context.SDL_facade.play_sound_effect("res/sound_effects/monsterkill.wav");
//        //test 2 sound effects:
//        context.SDL_facade.play_sound_effect("res/sound_effects/headshot.wav");
    }

    void StartUpState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();

        PressedKeys keys = this->_context.SDL_facade.get_keys();

        for(auto key : keys){
            switch (key) {
                case Key::ENTER:
                    this->_context.SDL_facade.stop_music();
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image(VIDYA_RUNPATH + "res/startscreen.bmp", CoordinateDouble{0,0});
        this->_context.SDL_facade.render_buffer();
    }
}