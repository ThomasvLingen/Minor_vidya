//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"

SDLFacade::SDLFacade() {
    //todo
}

SDLFacade::~SDLFacade() {
    //todo
}

bool SDLFacade::init() {

    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        printf("Something went wrong while initting: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL_TTF
    if (TTF_Init() < 0) {
        printf("Something went wrong while initting SDL_TTF!%s\n", TTF_GetError());
    };

    // Init window
    printf("initting window\n");
    if (!this->init_window()) {
        return false;
    }

    printf("initting renderer\n");
    if (!this->init_renderer()) {
        return false;
    }

    printf("initting done\n");
    return true;
}

bool SDLFacade::init_renderer()
{
    // Attempt to make a software renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    if (this->renderer != NULL) {
        printf("Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering\n");
        return true;
    } else {
        printf("Something went wrong while making a renderer! : %s\n", SDL_GetError());
        return false;
    }
}

bool SDLFacade::init_window() {
    window = SDL_CreateWindow("Vidya gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500,
                              500, SDL_WINDOW_SHOWN);
    if(window != NULL) {
        screenSurface = SDL_GetWindowSurface(window);
        return true;
    } else {
        printf("Something went wrong while making a window! : %s\n", SDL_GetError());
        return false;
    }
}

void SDLFacade::clear_screen() {
    // Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
}

void SDLFacade::draw_line(const double &x1, const double &y1, const double &x2, const double &y2, const Color &color) {
    //todo
    SDL_RenderDrawLine(renderer, 0, 0, 20, 30);
    //SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

}

void SDLFacade::render_buffer() const {
    //todo
}

void SDLFacade::handle_sdl_events() {
    //todo
}

std::vector <Key, std::allocator<Key>> SDLFacade::get_keys() const {
    //todo
    return std::vector < Key, std::allocator < Key >> ();
}

void SDLFacade::draw_text(string text, FontType font) const {
    //todo
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
