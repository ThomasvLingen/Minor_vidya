//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"

SDLFacade::SDLFacade(const function<void()>& callback_func )
: _quit_callback(callback_func)
{
    _init_possible_keys();
}

SDLFacade::~SDLFacade() {
    //todo
}

void SDLFacade::_init_possible_keys() {
    // Init _possible_keys
    _possible_keys.insert(pair<SDL_Keycode, Key>(SDLK_w, W));
    _possible_keys.insert(pair<SDL_Keycode, Key>(SDLK_a, A));
    _possible_keys.insert(pair<SDL_Keycode, Key>(SDLK_s, S));
    _possible_keys.insert(pair<SDL_Keycode, Key>(SDLK_d, D));
    _possible_keys.insert(pair<SDL_Keycode, Key>(SDLK_ESCAPE, ESC));
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
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_KEYDOWN:
                _handle_key_pressed_event(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _handle_key_released_event(event.key.keysym.sym);
                break;
            case SDL_QUIT:
                _quit_callback();
                break;
            case SDL_WINDOWEVENT:
                _handle_window_event(&event);
                break;
            default:
                break;
        }
    }
}

std::vector <Key, std::allocator<Key>> SDLFacade::get_keys() const {
    //todo
    return std::vector < Key, std::allocator < Key >> ();
}

void SDLFacade::draw_text(string text, FontType font) const {
    //todo
}

void SDLFacade::set_height(const int &screen_height) {
    this->_height = screen_height;
}

int SDLFacade::get_height() const {
    return this->_height;
}

void SDLFacade::set_width(const int &screen_width) {
    this->_width = screen_width;
}

int SDLFacade::get_width() const {
    return this->_width;
}

void SDLFacade::_handle_key_pressed_event(SDL_Keycode key) {
    map<SDL_Keycode, Key>::iterator it;
    it = this->_possible_keys.find(key);

    // Check if SDL_Keycode needs to be handled
    if(it != this->_possible_keys.end()){
        this->_keys_down.push_back(it->second);
    }
}

void SDLFacade::_handle_key_released_event(SDL_Keycode key) {
    map<SDL_Keycode, Key>::iterator it_possible;
    it_possible = _possible_keys.find(key);

    // Check if SDL_Keycode needs to be handled
    if(it_possible != _possible_keys.end()){
        vector<Key>::iterator it_down;
        it_down = find(this->_keys_down.begin(), this->_keys_down.end(), it_possible->second);

        // Check if released key is in _keys_down
        if(it_down != _keys_down.end()){
            _keys_down.erase(it_down);
        }
    }
}

void SDLFacade::_handle_window_event(SDL_Event* event){
    switch(event->window.event){
        case SDL_WINDOWEVENT_RESIZED:
            this->_width = event->window.data1;
            this->_height = event->window.data2;
            break;
        default:
            break;
    }
}