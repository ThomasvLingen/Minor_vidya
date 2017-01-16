//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_PLAYER_HPP
#define MINOR_VIDYA_PLAYER_HPP

#include <memory>
#include "../engine/domain/World.hpp"
#include "../engine/domain/PointOfView.hpp"
#include "../engine/domain/CoordinateDouble.hpp"
#include "../engine/raycasting/RaycastingVector.hpp"
#include "VectorUtil.hpp"
#include "Level.hpp"
#include "../engine/KeyStrokes.hpp"
#include "weapons/Weapon.hpp"
#include "exceptions/WeaponIsNullptrException.hpp"

namespace GameLogic {

    using Engine::CoordinateDouble;
    using Engine::RaycastingVector;
    using Engine::PointOfView;
    using Engine::World;
    using Engine::Keys;
    using Engine::Input;
    using Engine::Key;
    using std::string;

    class Level;

    class Player : public PointOfView, public Drawable {

    public:
        Player(CoordinateDouble position, SDLFacade& SDL_facade);
        ~Player();

        int get_health();
        int get_total_health();

        bool is_at(int x, int y);
        void set_level(SPTR_Level level);
        void handleInput(Input keys);
        virtual void update(int timeSinceLastUpdate);

        Weapon* get_weapon();
        void give_weapon(Weapon* weapon);

        virtual void draw() override;

    private:
        SPTR_Level _level;

        const double _MOVE_SPEED = 0.003;
        const double _STRAFE_SPEED = 0.004;
        const double _ROT_SPEED = 0.003;
        double _yAccel = 0;
        double _xAccel = 0;
        double _rotation = 0;
        double _next_tile = 0.5;
        bool _action_released = true;

        Tile* _current_tile;

        int _total_health = 80;
        int _health;

        void _move_player(int timeSinceLastUpdate);
        void _rotate_player(int timeSinceLastUpdate);
        void _mov_forward();
        void _mov_backward();
        void _move_left();
        void _move_right();
        void _rot_right();
        void _rot_left();

        bool _new_tile();

        void _set_new_current_tile();
        void _try_trigger();
        void _do_action();
        Tile* _get_facing_tile();
        void _draw_tile_usage();
        void _draw_punch_usage();
        void _draw_crosshair_usage();
        void _shoot();
        void _next_weapon();
        void _previous_weapon();

        vector<Weapon*> _weapons;
        int _current_weapon_index = 0;

        const string _action_hand_path {"res/hand.png"};
        const string _action_punch_path {"res/punch.png"};
        const string _crosshair_path {"res/crosshair.png"};

        void _melee();

        /*
         * int health
         * obj Inventory -> vector<items>
         * GrabItem();
         * PlaceItem();
         *
         */

    };

    typedef std::shared_ptr<Player> SPTR_Player;
}

#endif //MINOR_VIDYA_PLAYER_HPP
