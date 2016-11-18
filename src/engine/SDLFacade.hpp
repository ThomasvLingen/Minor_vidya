//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "domain/Color.hpp"
#include "raycasting/RayCastingTypes.hpp"
#include "domain/CoordinateDouble.hpp"
#include "KeyStrokes.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


namespace Engine {
    using std::string;
    using std::map;
    using std::vector;
    using std::pair;
    using std::function;
    using std::find;
    using std::cout;
    using std::endl;


    enum class FontType {verdana, roman, alterebro_pixel, alterebro_pixel_plus};


    class SDLFacade {
    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font*> _fonts;

        map<SDL_Keycode, Key> _possible_keys = {
            {SDLK_w, Key::W},
            {SDLK_a, Key::A},
            {SDLK_s, Key::S},
            {SDLK_d, Key::D},
            {SDLK_e, Key::E},
            {SDLK_q, Key::Q},
            {SDLK_ESCAPE, Key::ESC}
        };

        SDL_Window* _window = nullptr;
        SDL_Surface* _screenSurface = nullptr;
        SDL_Renderer* _renderer = nullptr;

        int _width;
        int _height;

        function<void()> _quit_callback;

    public:
        SDLFacade(const function<void()>& callback_func);

        virtual ~SDLFacade();

        bool init();

        void clear_screen(); //draws the background

        void draw_line(const CoordinateDouble& line_start, const CoordinateDouble& line_end, const Color& color);

        void draw_rect(const CoordinateDouble& rect_start, const int width, const int height, const Color& color);

        void draw_image(const std::string path, const CoordinateDouble& coordinates);

        void render_buffer() const;

        void handle_sdl_events();

        PressedKeys get_keys() const;

        bool draw_text(const string& text, const FontType& font, const Color& color,
                       const CoordinateDouble& position) const;

        void set_height(const int& screen_height);

        int get_height() const;

        void set_width(const int& screen_width);

        int get_width() const;

        int get_ticks() const;

        void delay_millis(const int millis) const;

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool _init_window();
        bool _init_renderer();
        bool _init_fonts();
        bool _load_font(const string& path, const FontType& font_type, uint8_t size);
    };
}


#endif //MINOR_VIDYA_SDLFACADE_HPP
