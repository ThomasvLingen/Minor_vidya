//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_LEVEL_HPP
#define MINOR_VIDYA_LEVEL_HPP

#include "../engine/domain/World.hpp"
#include "../engine/domain/TileObject.hpp"
#include "Tile.hpp"
#include "../engine/domain/PointOfView.hpp"
#include "entities/EnemyFactory.hpp"
#include <vector>
#include <memory>

namespace GameLogic {

    using std::vector;
    using Engine::CoordinateDouble;
    using Engine::CoordinateInt;
    using Engine::TileObject;
    using Engine::PointOfView;
    using Engine::AssetsManager;

    class Player;
    typedef vector<vector<Tile*>> TileMap;

    class Level : public Engine::World {

    private:
        TileMap _field;
        CoordinateDouble _spawnpoint;
        Player& _player;
        bool _level_won = false;

        /*
         * WorldParser
         *      ->
         *          field = GetLevel(string levelcode);
         *          tileset = GetLevelTileSet(string levelcode);
         */

    public:
        Level(Player& player, TileMap field, CoordinateDouble spawnpoint, Engine::SPTR_AssetsManager assets);
        Level(Player& player, Engine::SPTR_AssetsManager assets);
        Level(const Level& obj);
        virtual ~Level();

        EnemyFactory entity_factory;

        void update(int delta_time) override;

        TileObject* get_tile(CoordinateInt coordinate) override;

        Tile* get_tile_in_level(CoordinateInt coordinate);

        CoordinateDouble get_spawnpoint();
        void set_spawnpoint(CoordinateDouble coordinate);

        TileMap get_field();
        void set_field( TileMap field);

        PointOfView& get_pov() override;

        Player& get_player();

        void handle_input(Engine::Input keys) override;

        void set_level_over();

        bool is_level_over();

        Entity* get_entity(int x, int y);

        bool has_entity(int x, int y);

        void kill_entity(int x, int y);

        int in_game_ticks = 0;
        int start_ticks;

    };

    typedef std::shared_ptr<Level> SPTR_Level;
}

#endif //MINOR_VIDYA_LEVEL_HPP
