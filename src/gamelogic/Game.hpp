//
// Created by jazula on 11/9/16.
//

#ifndef MINOR_VIDYA_GAME_HPP
#define MINOR_VIDYA_GAME_HPP

#include "../engine/SDLFacade.hpp"
#include "../engine/raycasting/Raycasting.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include "state/IGameState.hpp"
#include "../engine/PathUtil.hpp"
#include "Player.hpp"

namespace GameLogic {

    using State::SPTR_IGameState;
    using Engine::Raycasting;
    using Engine::SDLFacade;
    using Engine::WorldPTR;
    using Engine::PathUtil;

    class Player;

    class Game {
    public:
        Game();
        void run();

        SDLFacade SDL_facade;
        Raycasting raycasting_engine;
        bool running;

        void init_states();
        void set_new_state(SPTR_IGameState state);
        bool load_Level(std::string file_location);
        SPTR_Level get_level();

    private:
        void _init_sound_effects();
        void _init_weapons();

        SPTR_IGameState _current_state;
        SPTR_IGameState _new_state;

        SPTR_Level _level;
        SPTR_Player _player;
    };
}


#endif //MINOR_VIDYA_GAME_HPP
