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


    enum class FontType {alterebro_pixel};
    typedef vector<Uint32> ImageBuffer;

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
        SDL_Texture* _screen_buffer = nullptr;

        int _width;
        int _height;

        function<void()> _quit_callback;

    public:
        SDLFacade(const function<void()>& callback_func);
        virtual ~SDLFacade();

        bool init();

        PressedKeys get_keys() const;
        void handle_sdl_events();

        void clear_screen(); //draws the background
        void draw_line(const CoordinateInt& line_start, const CoordinateInt& line_end, const Color& color);
        bool draw_text(const string& text, const FontType& font, const Color& color,
                       const CoordinateInt& position) const;
        void draw_pixel_screen_buffer(const CoordinateInt& position, Uint32 pixel);
        void update_screen_buffer();
        void render_buffer() const;

        void set_height(const int& screen_height);
        void set_width(const int& screen_width);
        int get_height() const;
        int get_width() const;

        void delay_millis(const int millis) const;
        int get_ticks() const;

        ImageBuffer get_image_buffer(const string& path);

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool _init_window();
        bool _init_renderer();
        bool _init_screen_buffer();
        bool _init_fonts();
        bool _load_font(const string& path, const FontType& font_type, uint8_t size);
    };
}


#endif //MINOR_VIDYA_SDLFACADE_HPP
