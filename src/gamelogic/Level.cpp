//
// Created by waseland on 11/7/16.
//

#include "Level.hpp"
#include "Player.hpp"

namespace GameLogic {

    using std::vector;

    Level::Level(Player& player, vector<vector<Tile*>> field, CoordinateDouble spawnpoint, Engine::SPTR_AssetsManager assets)
    : World(assets)
    , _field(field)
    , _player(player)
    , _spawnpoint(spawnpoint)
    {
    }

    Level::Level(Player& player, Engine::SPTR_AssetsManager assets)
    : World(assets)
    , _player(player)
    {
    }

    Level::Level(const Level& obj)
    : World(obj.assets)
    , _field(obj._field)
    , _spawnpoint(obj._spawnpoint)
    , _player(obj._player)
    {
    }

    Level::~Level()
    {
        for (auto row : this->_field) {
            for (auto tile : row) {
                delete tile;
            }
        }
    }

    /// \brief update every tile from this level
    void Level::update(int delta_time)
    {
        for (auto row : this->_field) {
            for (auto tile : row) {
                if (tile != nullptr) {
                    tile->update(delta_time);
                }
            }
        }

        this->_player.update(delta_time);
    }

    CoordinateDouble Level::get_spawnpoint()
    {
        return this->_spawnpoint;
    }

    TileObject* Level::get_tile(int x, int y)
    {
        return _field[x][y];
    }

    PointOfView& Level::get_pov()
    {
        return this->_player;
    }

    void Level::handle_input(Engine::PressedKeys keys)
    {
        this->_player.handleInput(keys);
    }

    void Level::set_spawnpoint(CoordinateDouble coordinate)
    {
        this->_spawnpoint = coordinate;
    }

    void Level::set_field(vector<vector<Tile*>> field)
    {
        this->_field = field;
    }

    vector<vector<Tile*>> Level::get_field()
    {
        return this->_field;
    }
}