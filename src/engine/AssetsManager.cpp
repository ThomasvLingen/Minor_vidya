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

        for (auto& animation_map_pair : this->_known_animations) {
            for (auto animation_frame : animation_map_pair.second) {
                delete animation_frame;
            }
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
    /// \return Whether or not initialising the animation map has succeeded
    bool AssetsManager::_init_animation_map()
    {
        bool success = true;

        // Load in all animations
        success &= this->_load_animation("soldier_idle", "res/AW_soldier.bmp", 0, 16, 16, 4);

        return success;
    }

    /// \brief Loads an animation, and puts is in the _known_animations map
    /// \param animation_name Name of the animation, which can later be used to retrieve it
    /// \param animation_source Relative path to the .bmp file in which the animation frames can be found
    /// \param row Row at which the animation can be found
    /// \param width Width of one animation frame in pixels
    /// \param height Height of one animation frame in pixels
    /// \param animation_frames Number of frames this animation has
    /// \return Whether or not the animation was successfully loaded
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
    /// \brief Wrapper method for the SDLFacade::load_animation method
    ///
    /// Made purely so that the implementation of this method can be easily replaced
    ///
    /// \return
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

    /// \brief Fetches the animation from the known animations.
    /// Throws an exception if the animation is not found
    /// \param name Name of the animation to fetch
    /// \return Vector of images which make up the animation (animation frames)
    vector<ImageBuffer*> AssetsManager::get_animation(string name)
    {
        return this->_known_animations.at(name);
    }
}
