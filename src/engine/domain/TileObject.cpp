#include "TileObject.hpp"
#include "../../util/UnusedMacro.hpp"


namespace Engine {
    TileObject::TileObject(ImageBuffer& texture)
    : _texture(texture)
    {
        for (size_t i = 0; i < 4; i++) {
            this->_neighbour_tiles.push_back(nullptr);
        }
    }

    TileObject::~TileObject()
    {
        for(Entity* entity : _entities){
            delete entity;
        }
    }

    /// \brief update all objects in this particular tile.
    void TileObject::update(int delta_time)
    {
        UNUSED(delta_time)
        // TODO: Implement this
    }

    void TileObject::set_wall(bool has_wall)
    {
        this->_wall = has_wall;
    }

    void TileObject::set_color(Color color)
    {
        this->_color = color;
    }

    void TileObject::set_tile_neighbour(TileObject* tile, Direction direction)
    {
        this->_neighbour_tiles[(size_t)direction] = tile;
    }

    TileObject* TileObject::get_tile_neighbour(Direction direction)
    {
        return this->_neighbour_tiles[(size_t)direction];
    }

    bool TileObject::is_wall()
    {
        return this->_wall;
    }

    Color TileObject::get_color()
    {
        return this->_color;
    }

    ImageBuffer& TileObject::get_texture()
    {
        return this->_texture;
    }

    vector<Entity*> TileObject::get_entities()
    {
        return _entities;
    }
}
