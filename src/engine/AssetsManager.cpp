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

    bool AssetsManager::init( string& texture_source, size_t tile_width, size_t tile_height, size_t tile_count )
    {
        bool success = true;
        success &= this->_init_texture_map( texture_source, tile_width, tile_height, tile_count );

        return success;
    }

    bool AssetsManager::_init_texture_map( string& texture_source, size_t tile_width, size_t tile_height, size_t tile_count )
    {
        bool success = true;

        // We put an empty texture at index 0, since an empty space should not have an index
        // We can now directly map tile IDs to textures!
        this->_known_textures[0] = new ImageBuffer();

        TextureMap texture_map = this->_SDL_facade.get_tileset_buffers(VIDYA_RUNPATH + "res/Wolfswapebobpepper.bmp", 64, 64, 108);
        //TODO don't hardcode this, perhaps place it in the config file
        //TODO change the name of this file
        if (texture_map.size() == 0) {
            success = false;
        } else {
            this->_known_textures[0] = new ImageBuffer();
            for (auto tile_pair : this->_tileset_map_to_id) {
                this->_known_textures[tile_pair.first] = texture_map[tile_pair.second];
            }
        }

        return success;
    }

    ImageBuffer& AssetsManager::get_texture(int id)
    {
        return *this->_known_textures.at(id);
    }
}
