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
    , _spawnpoint(spawnpoint)
    , _player(player)
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
            for (Tile* tile : row) {
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

    TileObject* Level::get_tile(CoordinateInt coordinate)
    {
        return this->_field[coordinate.x][coordinate.y];
    }

    Tile* Level::get_tile_in_level(CoordinateInt coordinate)
    {
        return this->_field[coordinate.x][coordinate.y];
    }

    Tile* Level::get_tile_in_level(CoordinateInt coordinate)
    {
        return _field[coordinate.x][coordinate.y];
    }

    PointOfView& Level::get_pov()
    {
        return this->_player;
    }

    Player& Level::get_player()
    {
        return this->_player;
    }

    void Level::handle_input(Engine::Input keys)
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

    void Level::set_level_over()
    {
        this->_level_won = true;
    }

    bool Level::is_level_over()
    {
        return this->_level_won;
    }
}