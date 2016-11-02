//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"
#include <iostream>

SDLFacade::SDLFacade() {
    //todo
}

SDLFacade::~SDLFacade() {
    //todo
    delete _window;
    delete _screenSurface;
    delete _renderer;

    for(auto font : this->_fonts){
        delete font.second;
    }
}

bool SDLFacade::init() {

    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        //std::cout <<  "Something went wrong while initting: " + SDL_GetError() << std::endl;
        return false;
    }

    // Init SDL_TTF
    if (TTF_Init() < 0) {
        //std::cout << "Something went wrong while initting SDL_TTF!" + TTF_GetError() << std::endl;
    };

    // Init window
    //std::cout << "initializing window" << std::endl;
    if (!this->_init_window()) {
        return false;
    }

    //std::cout << "initializing renderer" << std::endl;
    if (!this->_init_renderer()) {
        return false;
    }

    if (!this->_init_fonts()) {
        std::cout << "Your fonts could not be initted" << std::endl;
        return false;
    }

    //std::cout << "initialization done" << std::endl;
    return true;
}

bool SDLFacade::_init_renderer()
{
    // Attempt to make a software renderer
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_SOFTWARE);
    if (this->_renderer != nullptr) {
        //std::cout << "Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering" << std::endl;
        return true;
    } else {
        //std::cout << "Something went wrong while making a renderer! : " + SDL_GetError() << std::endl;
        delete _renderer;
        return false;
    }
}

bool SDLFacade::_init_window() {
    _window = SDL_CreateWindow("Vidya game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500,
                              500, SDL_WINDOW_SHOWN);
    if(_window != nullptr) {
        _screenSurface = SDL_GetWindowSurface(_window);
        return true;
    } else {
        //std::cout << "Something went wrong while making a window! : " + SDL_GetError() << std::endl;
        delete _window;
        return false;
    }
}

void SDLFacade::clear_screen() {
    // Draw background
    SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, 0x00, 0x00, 0x00));
}

void SDLFacade::draw_line(const CoordinateDouble &position1, const CoordinateDouble &position2, const Color &color) {

    SDL_SetRenderDrawColor(_renderer, color.r_value, color.g_value, color.b_value, 255);
    SDL_RenderDrawLine(_renderer, position1.x, position1.y, position2.x, position2.y);

}

void SDLFacade::render_buffer() const {
    //todo
    // Update window surface
    SDL_UpdateWindowSurface(_window);
}


void SDLFacade::handle_sdl_events() {
    //todo
}

std::vector <Key, std::allocator<Key>> SDLFacade::get_keys() const {
    //todo
    return std::vector < Key, std::allocator < Key >> ();
}

bool SDLFacade::draw_text(const string &text, const FontType &font, const Color &color, const CoordinateDouble &position) const {
    SDL_Color render_color = { color.r_value, color.g_value, color.b_value, 255 };
    TTF_Font* render_font = nullptr;
    SDL_Surface* text_surface = nullptr;
    SDL_Texture* text_texture = nullptr;

    try{
        render_font = _fonts.at(font);

        text_surface = TTF_RenderText_Solid(render_font, text.c_str(), render_color);
        text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
        SDL_Rect text_rect;
        text_rect.x = position.x;
        text_rect.y = position.y;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;

        SDL_RenderCopy(this->_renderer, text_texture, nullptr, &text_rect);
        SDL_FreeSurface(text_surface);

        return true;
    } catch (int exception){
        delete render_font;
        delete text_surface;
        delete text_texture;
        return false;
    }
}

void SDLFacade::set_height(const int &screen_height, const int &screen_width) {
    //todo
}

int SDLFacade::get_height() const {
    //todo
    return 0;
}

void SDLFacade::set_width(const int &screen_height, const int &screen_width) {
    //todo
}

int SDLFacade::get_width() const {
    //todo
    return 0;
}

void SDLFacade::_handle_quit_event() {
    //todo
}

void SDLFacade::_handle_key_event() {
    //todo
}

bool SDLFacade::_init_fonts(){
    TTF_Font* blue_highway_font = TTF_OpenFont("res/blue_highway_rg.ttf", 30);

    if (blue_highway_font == nullptr) {
        printf("Could not open blue_highway_rg.ttf [%s]\n", TTF_GetError());
    }

    _fonts[FontType::blue_highway_rg] = blue_highway_font;
    return true;
}
