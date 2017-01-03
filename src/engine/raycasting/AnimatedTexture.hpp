//
// Created by mafn on 12/20/16.
//

#ifndef MINOR_VIDYA_ANIMATEDTEXTURE_HPP
#define MINOR_VIDYA_ANIMATEDTEXTURE_HPP

#include "../ImageTypes.hpp"
#include "../interface/Updatable.hpp"
#include <vector>

namespace Engine {
    using std::vector;

    class AnimatedTexture : public Updatable {
    public:
        AnimatedTexture(vector<ImageBuffer*> textures, vector<size_t> texture_active_times, size_t tex_width, size_t tex_height);
        virtual ~AnimatedTexture();

        virtual void update(int delta_time) override;

        ImageBuffer& get_texture();
        size_t get_texture_width();
        size_t get_texture_height();
    private:
        vector<ImageBuffer*> _textures;
        vector<size_t> _texture_active_times;
        size_t _tex_width;
        size_t _tex_height;

        // TODO: This might be better solved with an iterator
        size_t _current_texture_index;
        void _select_next_texture();

        size_t _time_since_last_texture_switch;
        size_t _get_current_texture_active_time();
    };
}


#endif //MINOR_VIDYA_ANIMATEDTEXTURE_HPP
