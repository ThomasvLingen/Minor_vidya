//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_LEVEL_HPP
#define MINOR_VIDYA_LEVEL_HPP

#include "../engine/domain/World.hpp"
#include "../engine/domain/TileObject.hpp"
#include "Tile.hpp"
#include "../engine/domain/PointOfView.hpp"
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

    class Level : public Engine::World {

    private:
        vector<vector<Tile*>> _field; //TODO create a typedef for this
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
        Level(Player& player, vector<vector<Tile*>> field, CoordinateDouble spawnpoint, Engine::SPTR_AssetsManager assets);
        Level(Player& player, Engine::SPTR_AssetsManager assets);
        Level(const Level& obj);
        virtual ~Level();

        void update(int delta_time) override;

        TileObject* get_tile(CoordinateInt coordinate) override;

        Tile* get_tile_in_level(CoordinateInt coordinate);

        CoordinateDouble get_spawnpoint();
        void set_spawnpoint(CoordinateDouble coordinate);

        vector<vector<Tile*>> get_field();
        void set_field(vector<vector<Tile*>> field);

        PointOfView& get_pov() override;

        Player& get_player();

        void handle_input(Engine::Input keys) override;

        void set_level_over();

        bool is_level_over();
    };

    typedef std::shared_ptr<Level> SPTR_Level;
}

#endif //MINOR_VIDYA_LEVEL_HPP
