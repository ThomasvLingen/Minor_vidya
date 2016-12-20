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

    AssetsManager::~AssetsManager()
    {
        for (auto& texture_map_pair : this->_known_textures) {
            delete texture_map_pair.second;
        }
    }

    bool AssetsManager::init( string texture_source, size_t tile_width, size_t tile_height, size_t tile_count )
    {
        bool success = true;

        success &= this->_init_texture_map( texture_source, tile_width, tile_height, tile_count );
        success &= this->_init_animation_map();

        return success;
    }

    bool AssetsManager::_init_texture_map( string texture_source, size_t tile_width, size_t tile_height, size_t tile_count )
    {
        bool success = true;

        TextureMap texture_map = this->_SDL_facade.get_tileset_buffers( texture_source, tile_width, tile_height, tile_count );
        if (texture_map.size() == 0) {
            success = false;
        } else {
            // We put an empty texture at index 0, since an empty space should not have an index
            // We can now directly map tile IDs to textures!
            this->_known_textures[0] = new ImageBuffer();

            for (auto tile_pair : texture_map) {
                this->_known_textures[tile_pair.first] = tile_pair.second;
            }
        }

        return success;
    }

    /// \brief This initialises the animation map, which contains all ImageBuffers for animations
    /// This is all hardcoded until a better solution is found
    ///
    /// \return
    bool AssetsManager::_init_animation_map()
    {
        bool success = true;

        // Load in all animations
        success &= this->_load_animation("soldier_idle", "res/AW_soldier.bmp", 0, 16, 16, 4);

        return success;
    }

    bool AssetsManager::_load_animation(string animation_name, string animation_source, size_t row, size_t width,
                                        size_t height, size_t animation_frames)
    {
        vector<ImageBuffer*> animation_textures = this->_get_animation(animation_source, row, width, height, animation_frames);

        if (animation_textures.size() > 0) {
            this->_known_animations[animation_name] = animation_textures;

            return true;
        }

        return false;
    }

    vector<ImageBuffer*> AssetsManager::_get_animation(string sprite_sheet, size_t row, size_t width, size_t height,
                                                       size_t animation_frames)
    {
        return this->_SDL_facade.load_animation(sprite_sheet, row, width, height, animation_frames);
    }

    ImageBuffer* AssetsManager::get_texture(int id)
    {
        return this->_known_textures.at(id);
    }
    ImageBuffer* AssetsManager::get_entity_texture( string texture_source )
    {
        return this->_SDL_facade.load_image_buffer(texture_source);
    }

    vector<ImageBuffer*> AssetsManager::get_animation(string name)
    {
        return this->_known_animations.at(name);
    }
}
