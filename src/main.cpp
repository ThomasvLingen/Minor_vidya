#include <iostream>
#include "SDLFacade.hpp"

int main()
{
    std::cout << "Hello world" << std::endl;

    SDLFacade sdlFacade = SDLFacade();
    if(sdlFacade.init()){
        std::cout << "Start" << std::endl;
        while(true) {
            sdlFacade.clear_screen();
            sdlFacade.draw_line(0, 0, 20, 20, Color());
            sdlFacade.render_buffer();
            SDL_Delay(1000);
        }
    } else {
        std::cout << "Failed" << std::endl;
    }
    std::cin;

    return 0;
}

