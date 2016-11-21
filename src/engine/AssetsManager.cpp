//
// Created by mafn on 11/21/16.
//

#include "AssetsManager.hpp"

namespace Engine {
    AssetsManager::AssetsManager(SDLFacade& SDL_facade)
    : _SDL_facade(SDL_facade)
    {
    }

    bool AssetsManager::init()
    {
        bool success = true;

        success &= this->_init_texture_map();

        return success;
    }

    bool AssetsManager::_init_texture_map()
    {
        bool success = true;

        // We put an empty texture at index 0, since an empty space should not have an index
        // We can now directly map tile IDs to textures!
        this->_known_textures[0] = new ImageBuffer();
        // TODO: This should not be hardcoded here as soon as tiled integration works
        success &= this->_load_texture(1, "res/BrickWall.bmp");
        success &= this->_load_texture(2, "res/StoneWall.bmp");
        success &= this->_load_texture(3, "res/WoodWall.bmp");

        return success;
    }

    bool AssetsManager::_load_texture(int id, string path)
    {
        ImageBuffer* retrieved = new ImageBuffer(this->_SDL_facade.get_image_buffer(path));

        // If the size is zero, the SDL_Facade could not load the image
        if (retrieved->size() == 0) {
            cout << "The following texture could not be loaded: " << path << endl;
            return false;
        }

        this->_known_textures[id] = retrieved;
        return true;
    }

    ImageBuffer& AssetsManager::get_texture(int id)
    {
        return *this->_known_textures.at(id);
    }
}
