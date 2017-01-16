//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"
#include "../config.hpp"
#include "PathUtil.hpp"
#include <SDL2/SDL_image.h>

#include "exceptions/InvalidImageException.hpp"
#include "exceptions/InvalidSoundFileException.hpp"
#include "exceptions/InvalidWavFileException.hpp"
#include "exceptions/SoundeffectNotLoadedException.hpp"

namespace Engine {

    /// \brief Constructor of the class
    ///
    /// The given callback function will be saved. This function will be called on Quit-event
    /// \param callback_func The function that needs to be called on quit
    SDLFacade::SDLFacade(const function<void()>& callback_func )
    : _width(640)  // Initialise this, otherwise we get an uninitialised width and height,
    , _height(480) // resulting in wrong raycasting ray index values.
    , _quit_callback(callback_func)
    {

    }

    /// \brief Destructor of the class
    SDLFacade::~SDLFacade()
    {
        for (auto image : this->_images) {
            SDL_DestroyTexture(image.second);
        }

        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);

        for (auto sound_effect : this->_sound_effects) {
            Mix_FreeChunk(sound_effect.second);
        }

        this->stop_music();
        Mix_CloseAudio();
        Mix_Quit();

        for (auto font : this->_fonts) {
            TTF_CloseFont(font.second);
        }

        SDL_Quit();
    }

    /// \brief Initialiser for all class instance variables
    ///
    /// This method will initialize:
    /// * SDL
    /// * TTF
    ///
    /// This method calls the following functions:
    /// * _init_window()
    /// * _init_renderer()
    /// * _init_fonts()
    ///
    /// \return This function returns True if everything was successfully initialized, ohterwise it returns False
    bool SDLFacade::init()
    {
        // Init SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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

        if (!this->_init_screen_buffer()) {
            return false;
        }

        if (!this->_init_fonts()) {
            std::cout << "Your fonts could not be initted" << std::endl;
            return false;
        }

        if (Mix_OpenAudio(this->_frequency, this->_audio_format, this->_channels, this->_chunksize) == -1) {
            return false;
        }

        //std::cout << "initialization done" << std::endl;
        return true;
    }

    /// \brief Initialiser for the _renderer (SDL_Renderer)
    ///
    /// \return This function returns True if the _renderer was successfully initialized, ohterwise it returns False
    bool SDLFacade::_init_renderer()
    {
        Uint32 renderer_flags;

        if (Config::USE_VSYNC) {
            renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        } else {
            renderer_flags = SDL_RENDERER_SOFTWARE;
        }

        // Attempt to make a software renderer
        this->_renderer = SDL_CreateRenderer(this->_window, -1, renderer_flags);
        if (this->_renderer != nullptr) {
            //std::cout << "Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering" << std::endl;
            return true;
        } else {
            //std::cout << "Something went wrong while making a renderer! : " + SDL_GetError() << std::endl;
            SDL_DestroyRenderer(this->_renderer);
            return false;
        }
    }

    /// \brief Initialiser for the _window (SDL_Window)
    ///
    /// \return This function returns True if the _window was successfully initialized, ohterwise it returns False
    bool SDLFacade::_init_window()
    {
        this->_window = SDL_CreateWindow(Config::GAME_WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_width,
                                         this->_height, SDL_WINDOW_SHOWN);
        if (this->_window != nullptr) {
            return true;
        } else {
            //std::cout << "Something went wrong while making a window! : " + SDL_GetError() << std::endl;
            SDL_DestroyWindow(this->_window);
            return false;
        }
    }
    /// \brief Initialiser for the _screen_buffer (SDL_Texture)
    ///
    /// The format(SDL_PIXELFORMAT_ARGB8888) has been found to be the right one through testing. When using other formats, the images have a red/blue gradient or don't show at all
    ///
    /// \return This function returns True if the _screen_buffer was successfully initialized, ohterwise it returns False
    bool SDLFacade::_init_screen_buffer()
    {
        this->_screen_buffer = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                                 this->_width, this->_height);

        if (this->_screen_buffer != nullptr) {
            return true;
        } else {
            SDL_DestroyTexture(this->_screen_buffer);
            return false;
        }
    }

    /// \brief Draws a rectangle
    ///
    /// A rect will be drawn from the given coordinate with the given width and height The color is set first, secondly the rect is being drawn.
    ///
    /// \param rect_start Coordinate of the start of the rectangle
    /// \param width Width of the rectangle
    /// \param height Height of the rectangle
    /// \param color The color of the rectangle. The color class comes from the engine
    void SDLFacade::draw_rect(const CoordinateInt& rect_start, const int width, const int height, const Color& color)
    {
        SDL_Rect r;
        r.x = rect_start.x;
        r.y = rect_start.y;
        r.w = width;
        r.h = height;
        SDL_SetRenderDrawColor(this->_renderer, color.r_value, color.g_value, color.b_value, 255);
        SDL_RenderFillRect(this->_renderer, &r);
    }

    bool SDLFacade::_is_image_in_map(string path) {
        auto search_image = this->_images.find(path);
        return search_image != this->_images.end();
    }

    void SDLFacade::_add_image_in_map(string path) {

        SDL_Surface* image;
        try{
             image = IMG_Load(this->_get_absolute_path(path).c_str());
        }catch (const Exceptions::InvalidImageException& e){
            cout << "IMG_Load: " << IMG_GetError() << endl;
            cout << e.what() << endl;
        }
        SDL_Texture* image_texture = SDL_CreateTextureFromSurface(this->_renderer, image);
        this->_images.insert(std::make_pair(path, image_texture));

        SDL_FreeSurface(image);
    }



    /// \brief Draws an image
    ///
    /// An image will be drawn on the coordinates (Accepts only bmp files)
    ///
    /// \param path Path to image (if in res it is: res/imagename.bmp)
    /// \param coordinates Coordinates of where the image has to be drawn
    void SDLFacade::draw_image(const std::string path, const CoordinateInt& coordinates)
    {
        if (!this->_is_image_in_map(path)) {
            this->_add_image_in_map(path);
        }

        int w = 0, h = 0;

        if(SDL_QueryTexture(this->_images[path], NULL, NULL, &w, &h) != 0){ // get width en height from texture
            cout << "Draw_image: "  << SDL_GetError() << endl;
        }

        SDL_Rect src_r = {0, 0, w, h};
        SDL_Rect dest_r = {(int)coordinates.x, (int)coordinates.y, w, h};

        SDL_RenderCopy(this->_renderer, this->_images[path], &src_r, &dest_r);
    }

    /// \brief Draws a rectangle on the whole screen
    void SDLFacade::clear_screen()
    {
        SDL_RenderClear(this->_renderer);
    }

    /// \brief Draws a line
    ///
    /// A line will be drawn between the given coordinates. The color is set first, secondly the line is being drawn.
    ///
    /// \param line_start The first coordinate
    /// \param line_end The second coordinate
    /// \param color The color of the line. The color class comes from the engine
    void SDLFacade::draw_line(const CoordinateInt& line_start, const CoordinateInt& line_end, const Color& color)
    {
        SDL_SetRenderDrawColor(this->_renderer, color.r_value, color.g_value, color.b_value, 255);
        SDL_RenderDrawLine(this->_renderer, line_start.x, line_start.y, line_end.x, line_end.y);
    }

    /// \brief Change a single pixel
    ///
    /// A pixel will be drawn at the given coordinates.
    ///
    /// \param position The coordinate
    /// \param pixel The pixel value that you want to draw
    void SDLFacade::draw_pixel_screen_buffer(const CoordinateInt& position, Uint32 pixel)
    {
        this->_screen_buffer_pixels[position.x + (position.y * this->_width)] = pixel;
    }

    void SDLFacade::draw_background(Uint32 top_color, Uint32 bottom_color)
    {
        int w = this->_width;
        int h = this->_height;
        if (sizeof(wchar_t) == 4) { //use wmemset is wchar is 4 bytes long (32 bits)
            wmemset((wchar_t*) this->_screen_buffer_pixels, top_color, w * (h / 2));
            wmemset((wchar_t*) &this->_screen_buffer_pixels[w * (h / 2)], bottom_color, w * (h / 2));
        } else { //otherwise use the slow method
            for (int index = 0; index < w*(h/2); index++) {
                this->_screen_buffer_pixels[index] = top_color;
            }
            for (int index = w*(h/2); index < w*h; index++) {
                this->_screen_buffer_pixels[index] = bottom_color;
            }
        }
    }

    /// \brief Lock the screen buffer for pixel manipulating
    void SDLFacade::lock_screen_buffer()
    {
        int pitch;
        SDL_LockTexture(this->_screen_buffer, NULL, (void**) &this->_screen_buffer_pixels, &pitch);
    }

    /// \brief Unlock the screen buffer (it can no longer a manupulated)
    void SDLFacade::unlock_screen_buffer()
    {
        SDL_UnlockTexture(this->_screen_buffer);
    }

    /// \brief Update of _screen_buffer
    ///
    /// Copies the _screen_buffer (SDL_Texture) to the renderer
    void SDLFacade::update_screen_buffer()
    {
        SDL_RenderCopy(this->_renderer, _screen_buffer, NULL, NULL);

        SDL_DestroyTexture(this->_screen_buffer);

        this->_screen_buffer = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                                 this->_width, this->_height);
    }

    /// \brief Updates the window
    void SDLFacade::render_buffer() const
    {
        // Update window surface through renderer
        SDL_RenderPresent(this->_renderer);
    }

    /// \brief Function that handles all relevant SDL_Event types
    ///
    /// Currently the function support the following event types:
    /// * KeyEvents
    /// * QuitEvent
    /// * WindowEvents
    ///     - Resize
    /// Each supported event type has its own handler (or callback)
    void SDLFacade::handle_sdl_events()
    {
        // Clear _keys_released
        this->_input.keys_released.clear();

        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    this->_handle_key_pressed_event(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    this->_handle_key_released_event(event.key.keysym.sym);
                    break;
                case SDL_QUIT:
                    this->_quit_callback();
                    break;
                case SDL_WINDOWEVENT:
                    this->_handle_window_event(&event);
                    break;
                default:
                    break;
            }
        }
    }

    Input SDLFacade::get_input() const
    {
        //todo
        return this->_input;
    }

    /// \brief Draws text
    ///
    /// This method will draw the given text in the desired color and font on the given coordinate
    ///
    /// \param text The text that needs to be drawn
    /// \param font The font in which the text needs to be drawn
    /// \param color The color in which the text needs to be drawn
    /// \param position The coordinate at which the text will be drawn
    ///
    /// \return This function returns True if text is successfully drawn, ohterwise it returns False
    bool SDLFacade::draw_text(const string& text, const FontType& font, const Color& color,
                              const CoordinateInt& position) const
    {
        SDL_Color render_color = { color.r_value, color.g_value, color.b_value, 255 };
        TTF_Font* render_font = nullptr;
        SDL_Surface* text_surface = nullptr;
        SDL_Texture* text_texture = nullptr;

        try {
            render_font = this->_fonts.at(font);

            text_surface = TTF_RenderText_Solid(render_font, text.c_str(), render_color);
            text_texture = SDL_CreateTextureFromSurface(this->_renderer, text_surface);
            SDL_Rect text_rect;
            text_rect.x = position.x;
            text_rect.y = position.y;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(this->_renderer, text_texture, nullptr, &text_rect);
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);

            return true;
        } catch (int exception) {
            TTF_CloseFont(render_font);
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
            return false;
        }
    }

    void SDLFacade::set_height(const int& screen_height)
    {
        this->_height = screen_height;
    }

    int SDLFacade::get_height() const
    {
        return this->_height;
    }

    void SDLFacade::set_width(const int& screen_width)
    {
        this->_width = screen_width;
    }

    int SDLFacade::get_width() const
    {
        return this->_width;
    }

    /// \brief Initialiser for all fonts
    ///
    /// \return This function returns True if all fonts are successfully initialised, ohterwise it returns False
    bool SDLFacade::_init_fonts()
    {
        bool success = true;

        success &= _load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel, 30);
        success &= _load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel_plus, 60);
        success &= _load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel_medium, 45);
        success &= _load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel_small, 20);

        return success;
    }

    /// \brief Initialiser for one font
    ///
    /// \param path The path where the font is located
    /// \param font_type The enum which will be linked to the loaded font
    /// \param size The desired fontsize
    ///
    /// \return This function returns True if the font is successfully initialized, ohterwise it returns False
    bool SDLFacade::_load_font(const string& path, const FontType& font_type, uint8_t size)
    {
        TTF_Font* new_font = TTF_OpenFont(this->_get_absolute_path(path).c_str(), size);

        if (new_font == nullptr) {
            cout << "Could not open " << path << " " << TTF_GetError() << endl;
            return false;
        } else {
            this->_fonts[font_type] = new_font;
            return true;
        }
    }

    /// \brief Function that handles a SDL_KEYDOWN event
    ///
    /// Supported keys will be handled and, if not already present, added to the _keys_down vector.
    void SDLFacade::_handle_key_pressed_event(SDL_Keycode key)
    {
        for(auto it = this->_possible_keys.begin(); it != this->_possible_keys.end(); ++it){
            if(it->second == key){
                vector<Key>::iterator it_pressed = this->_input.keys_down.begin();
                // it_pressed might need to be 0 first time
                it_pressed = find(it_pressed, this->_input.keys_down.end(), it->first);

                if(it_pressed == this->_input.keys_down.end()){
                    this->_input.keys_down.push_back(it->first);
                }
            }
        }
    }

    /// \brief Function that handles a SDL_KEYUP event
    ///
    /// Supported keys will be handled and, if present, removed from the _keys_down vector.
    void SDLFacade::_handle_key_released_event(SDL_Keycode key)
    {
        for(auto it = this->_possible_keys.begin(); it != this->_possible_keys.end(); ++it){
            if(it->second == key){
                vector<Key>::iterator it_down = this->_input.keys_down.begin();
                // it_down might need to be 0 first time
                it_down = find(it_down, this->_input.keys_down.end(), it->first);

                if(it_down != this->_input.keys_down.end()){
                    this->_input.keys_down.erase(it_down);
                }

                this->_input.keys_released.push_back(it->first);
            }
        }

    }


    /// \brief Function that handles a SDL_WINDOWEVENT event
    ///
    /// Currently only handles SDL_WINDOWEVENT_RESIZED, setting the new width and height of the window.
    void SDLFacade::_handle_window_event(SDL_Event* event)
    {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                this->_width = event->window.data1;
                this->_height = event->window.data2;
                break;
            default:
                break;
        }
    }

    int SDLFacade::get_ticks() const
    {
        return SDL_GetTicks();
    }

    void SDLFacade::delay_millis(const int millis) const
    {
        SDL_Delay((uint32_t)millis);
    }

    /// \brief Function that returns a list of pixels
    ///
    /// Each pixel in the list is represented as Uint32
    ///
    /// \param position The position where a tile can be found (e.g. 1,3 / 2,2 / 4,0)
    /// \param tile_width The width of a single tile
    /// \param tile_height The height of a single tile
    /// \param tileset The image that contains all tile textures
    ///
    /// \return This function returns a list of Uint32
    ImageBuffer* SDLFacade::get_image_buffer(SDL_Surface* tileset, const CoordinateInt &position,
                                             const int tile_width, const int tile_height)
    {
        ImageBuffer pixels;

        int start_y_pos = position.y * tile_height;
        int end_y_pos = position.y * tile_height + tile_height;

        int start_x_pos = position.x * tile_width;
        int end_x_pos = position.x * tile_width + tile_width;

        int bytes_per_pixel = tileset->format->BytesPerPixel;

        for (int current_y = start_y_pos; current_y < end_y_pos; current_y++) {
            for (int current_x = start_x_pos; current_x < end_x_pos; current_x++) {
                Uint8 *pixel = (Uint8 *)tileset->pixels + current_y * tileset->pitch + current_x * bytes_per_pixel;
                pixels.push_back(*(Uint32*)pixel);
            }
        }
        return new ImageBuffer(pixels);
    }

    /// \brief Function that converts the tileset to multiple lists of pixels
    ///
    /// \param path The path on which the tileset can be found
    /// \param tile_width The width of each tile
    /// \param tile_height The height of each tile
    /// \param amount_of_tiles Number of tiles that are stored within the tileset
    ///
    /// \return Returns a map with an Id as key and a vector<Uint32> as value. The list is empty when the image could not be loaded
    TextureMap SDLFacade::get_tileset_buffers(const string path, const int tile_width, const int tile_height,
                                              const int amount_of_tiles)
    {
        TextureMap texture_map;
        // load image
        SDL_Surface* tileset = IMG_Load(this->_get_absolute_path(path).c_str());
        if (tileset == NULL) {
            // check of succeeded
            cout << "An error occurred while loading tileset " << path
                 << ". This occurred while trying to convert an image to pixels for a texture." << endl;
        } else {
            SDL_LockSurface(tileset);
            int amount_of_tiles_horizontally = tileset->w / tile_width;

            int y = 0;
            int x = 0;

            for (int id = 1; id <= amount_of_tiles; id++) {
                if (x == amount_of_tiles_horizontally) {
                    x = 0;
                    y++;
                }

                texture_map[id] = get_image_buffer(tileset, CoordinateInt{x, y}, tile_width, tile_height);
                x++;
            }

            SDL_FreeSurface(tileset);
        }

        return texture_map;
    }

    ImageBuffer* SDLFacade::load_image_buffer( const string path )
    {
        ImageBuffer pixels;
        SDL_Surface* texture = IMG_Load( path.c_str() );
        if ( texture == NULL ) {
            // check of succeeded
            cout << "An error occurred while loading tileset " << path
                << ". This occurred while trying to convert an image to pixels for a texture." << endl;
        }
        else {
            SDL_LockSurface( texture );

            int bytes_per_pixel = texture->format->BytesPerPixel;

            for ( int current_y = 0; current_y < texture->h; current_y++ ) {
                for ( int current_x = 0; current_x < texture->w; current_x++ ) {
                    Uint8* pixel = ( Uint8* ) texture->pixels + current_y * texture->pitch + current_x * bytes_per_pixel;
                    pixels.push_back( *( Uint32* ) pixel );
                }
            }

            SDL_FreeSurface( texture );
        }

        return new ImageBuffer( pixels );
    }

    /// \brief Plays a music file
    ///
    /// Music will be played if the path is correct. Supports: WAVE, MP3, MIDI etc. Be sure to call when you want the music to stop.
    /// If another play_music is called it will overwrite the old one.
    ///
    /// \param path to the file (if it's in res/music write: "res/music/filename.mp3")
    void SDLFacade::play_music(const string path)
    {
        this->stop_music();

        try {
            this->_music = Mix_LoadMUS(this->_get_absolute_path(path).c_str());
        } catch (const Exceptions::InvalidSoundFileException& e){
            cout << e.what() << endl;
        }

        Mix_FadeInMusic(this->_music, this->_loop_forever, this->_fade_in_time);
    }

    /// \brief Loads a sound effect
    ///
    /// Sound effect will be loaded in the map if the path is correct. Supports ONLY: WAVE. Plays multiple at once.
    ///
    /// \param name of the key you want to call the sound_effect
    /// \param path to the file (if it's in res/music write: "res/music/filename.wav")
    void SDLFacade::load_sound_effect(const string name, const string path) {
        if (this->_sound_effects.find(name) != this->_sound_effects.end()) { //key already exists
            return;
        }

        Mix_Chunk* sound_effect;
        try{
            sound_effect = Mix_LoadWAV(this->_get_absolute_path(path).c_str());
        }catch (const Exceptions::InvalidWavFileException& e){
            cout << e.what() << endl;
        }

        this->_sound_effects[name] = sound_effect;
    }

    /// \brief Plays a sound effect
    ///
    /// Sound effect will be played if the path is correct. Supports ONLY: WAVE. Plays multiple at once.
    ///
    /// \param name of the key that the sound_effect is linked to
    void SDLFacade::play_sound_effect(const string name)
    {
        try {
            if (this->_sound_effects.find(name) == this->_sound_effects.end()) { //if sound_effect is not loaded
            }
        } catch (const Exceptions::SoundeffectNotLoadedException& e){
            cout << e.what() << endl;
        }
        Mix_PlayChannel(this->_next_available_channel, this->_sound_effects.at(name), this->_play_once);
    }

    /// \brief Stops music from playing and free's the music
    void SDLFacade::stop_music()
    {
        if (this->_music != NULL) {
            Mix_FreeMusic(this->_music);
            this->_music = NULL;
        }
    }

    /// \brief get image width of path
    int SDLFacade::get_image_width(const std::string path)
    {
        SDL_Surface* image;
        int size = 0;


        try {
            image = IMG_Load(this->_get_absolute_path(path).c_str());
        } catch (const Exceptions::InvalidImageException& e){
            cout << e.what() << endl;
        }

        size = image->w;
        SDL_FreeSurface(image);

        return size;
    }

    string SDLFacade::_get_absolute_path(const string path)
    {
        return VIDYA_RUNPATH + path;
    }

    /// \brief Load an animation from a .bmp file and return it
    /// \param path Path of the .bmp which contains the animation
    /// \param row Row at which the animation can be found (0 indexed)
    /// \param width Width of one animation frame in pixels
    /// \param height Height of one animation frame in pixels
    /// \param animation_frames Number of frames the animation contains
    /// \return A vector of images, which make up the frames of the animation
    vector<ImageBuffer*> SDLFacade::load_animation(const string path, const size_t row, const size_t width,
                                                   const size_t height, const size_t animation_frames)
    {
        vector<ImageBuffer*> animation_textures;

        SDL_Surface* animation_source = IMG_Load(this->_get_absolute_path(path).c_str());

        if (animation_source == NULL) {
            cout << "An error occurred while loading animation " << path << endl;
        } else {
            SDL_LockSurface(animation_source);

            for (size_t animation_frame = 0; animation_frame < animation_frames; animation_frame++) {
                animation_textures.push_back(
                    this->get_image_buffer(animation_source, CoordinateInt {animation_frame, row}, width, height)
                );
            }

            SDL_FreeSurface(animation_source);
        }

        return animation_textures;
    }

}