#include "gamelogic/Game.hpp"
#ifdef _WIN32
#define SDL_main main
#endif // _WIN32


using GameLogic::Game;

int main()
{
    Game game;
    game.run();
    return 0;
}
