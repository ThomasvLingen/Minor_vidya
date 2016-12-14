//
// Created by mafn on 11/21/16.
//

#include "AssetsManager.hpp"
#include "PathUtil.hpp"

namespace Engine {
    AssetsManager::AssetsManager(SDLFacade& SDL_facade)
    : _SDL_facade(SDL_facade)
    {
    }

    bool AssetsManager::init( string texture_source, int tile_width, int tile_height, int tile_count )
    {
        bool success = true;
        success &= this->_init_texture_map( texture_source, tile_width, tile_height, tile_count );

        return success;
    }

    bool AssetsManager::_init_texture_map( string texture_source, int tile_width, int tile_height, int tile_count )
    {
        bool success = true;

        // We put an empty texture at index 0, since an empty space should not have an index
        // We can now directly map tile IDs to textures!
        this->_known_textures[0] = new ImageBuffer();

        TextureMap texture_map = this->_SDL_facade.get_tileset_buffers( texture_source, tile_width, tile_height, tile_count );
        if (texture_map.size() == 0) {
            success = false;
        } else {
            this->_known_textures[0] = new ImageBuffer();
            for (auto tile_pair : texture_map) {
                this->_known_textures[tile_pair.first] = tile_pair.second;
            }
        }

        return success;
    }

    ImageBuffer* AssetsManager::get_texture(int id)
    {
        return this->_known_textures.at(id);
    }
    ImageBuffer& AssetsManager::get_entity_texture( string texture_source )
    {
        return *this->_SDL_facade.load_image_buffer(texture_source);
    }
}
