//
// Created by mafn on 11/21/16.
//

#ifndef MINOR_VIDYA_ASSETSMANAGER_HPP
#define MINOR_VIDYA_ASSETSMANAGER_HPP

#include <map>
#include <memory>
#include "SDLFacade.hpp"
#include "ImageTypes.hpp"

namespace Engine {
    using std::map;
    using std::string;

    class AssetsManager {
    public:
        AssetsManager(SDLFacade& SDL_facade);

        bool init( string texture_source, size_t tile_width, size_t tile_height, size_t tile_count);
        ImageBuffer* get_texture(int id);
        ImageBuffer& get_entity_texture(string texture_source);
    private:
        TextureMap _known_textures;

        bool _init_texture_map( string texture_source, size_t tile_width, size_t tile_height, size_t tile_count );
        SDLFacade& _SDL_facade;

        // TODO: This can be removed since it's unused.
        // Although it might be good to set these on init so that they can be retrieved where needed (raycaster?)
        string _texture_source;
        size_t _tile_height;
        size_t _tile_width;
        size_t _tile_count;
    };

    typedef std::shared_ptr<AssetsManager> SPTR_AssetsManager;
}


#endif //MINOR_VIDYA_ASSETSMANAGER_HPP
