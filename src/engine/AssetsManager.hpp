//
// Created by mafn on 11/21/16.
//

#ifndef MINOR_VIDYA_ASSETSMANAGER_HPP
#define MINOR_VIDYA_ASSETSMANAGER_HPP

#include <map>
#include <memory>
#include "SDLFacade.hpp"

namespace Engine {
    using std::map;
    using std::string;

    class AssetsManager {
    public:
        AssetsManager(SDLFacade& SDL_facade);

        bool init( string& texture_source, size_t tile_width, size_t tile_height, size_t tile_count);
        ImageBuffer& get_texture(int id);
    private:
        TextureMap _known_textures;

        bool _init_texture_map( string& texture_source, size_t tile_width, size_t tile_height, size_t tile_count );
        bool _load_texture(int id, string path);
        SDLFacade& _SDL_facade;

        string _texture_source;
        size_t _tile_height;
        size_t _tile_width;
        size_t _tile_count;

        // TODO: This should not be hardcoded here as soon as tiled integration works
        // The second number is the position of the tile in the tilemap
        map<int, int> _tileset_map_to_id = {
            {1, 33},    // Brick wall
            {2, 1},     // Stone wall
            {3, 23},    // Wood wall
            {4, 106},   // swap-e 1
            {5, 107},   // swap-e 2
            {6, 108},   // swap-e 3
            {7, 69},    // white brick wall
            {8, 9},     // Prison
            {9, 13},    // Skeleton prison
            {10, 25},   // Steel door
            {11, 29},   // Blue steel wall
            {12, 47},   // Disgusting wall
            {13, 7}     // Bob texture
        };
    };

    typedef std::shared_ptr<AssetsManager> SPTR_AssetsManager;
}


#endif //MINOR_VIDYA_ASSETSMANAGER_HPP
