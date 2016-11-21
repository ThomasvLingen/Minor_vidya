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

        // TODO: This should not be hardcoded here as soon as tiled integration works
        success &= this->_load_texture(0, "res/BrickWall.bmp");
        success &= this->_load_texture(1, "res/StoneWall.bmp");
        success &= this->_load_texture(2, "res/WoodWall.bmp");

        return success;
    }

    bool AssetsManager::_load_texture(int id, string path)
    {
        vector<Uint32> retrieved = this->_SDL_facade.get_image_buffer(path);

        // If the size is zero, the SDL_Facade could not load the image
        if (retrieved.size() == 0) {
            cout << "The following texture could not be loaded: " << path << endl;
            return false;
        }

        this->_known_textures[id] = retrieved;
        return true;
    }
}
