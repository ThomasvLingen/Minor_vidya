//
// Created by mafn on 11/21/16.
//

#ifndef MINOR_VIDYA_ASSETSMANAGER_HPP
#define MINOR_VIDYA_ASSETSMANAGER_HPP

#include <map>
#include "SDLFacade.hpp"

namespace Engine {
    using std::map;
    using std::string;

    typedef map<int, ImageBuffer*> TextureMap;

    class AssetsManager {
    public:
        AssetsManager(SDLFacade& SDL_facade);

        bool init();
        ImageBuffer& get_texture(int id);

    private:
        TextureMap _known_textures;

        bool _init_texture_map();
        bool _load_texture(int id, string path);
        SDLFacade& _SDL_facade;
    };
}


#endif //MINOR_VIDYA_ASSETSMANAGER_HPP
