//
// Created by mafn on 12/20/16.
//

#include "AnimatedTexture.hpp"
#include "../exceptions/AnimatedSpriteInvalidException.hpp"

namespace Engine {

    /// \brief A constructor for the AnimatedTexture class
    ///
    /// Please note that this class makes a couple of assumptions.
    /// * Textures and texture_active_times map onto each other (same index!)
    /// * All ImageBuffers are of the same width and height
    /// * Ownership for ImageBuffer*'s in textures does not lie with AnimatedTexture
    ///
    /// \param textures The AnimatedTexture's textures to cycle through
    /// \param texture_active_times The time which a texture is active (in ms)
    /// \param tex_width The width of ALL the textures (in px)
    /// \param tex_height The height of ALL the textures (in px)
    AnimatedTexture::AnimatedTexture(vector<ImageBuffer*> textures, vector<size_t> texture_active_times, size_t tex_width, size_t tex_height)
    : _textures(textures)
    , _texture_active_times(texture_active_times)
    , _tex_width(tex_width)
    , _tex_height(tex_height)
    , _current_texture_index(0)
    , _time_since_last_texture_switch(0)
    {
        // Verification of passed parameters
        if (this->_textures.size() != this->_texture_active_times.size()) {
            throw Exceptions::AnimatedSpriteInvalidException();
        }
    }

    AnimatedTexture::~AnimatedTexture()
    {

    }

    /// \brief Get the currently active texture
    /// This is a ref since we always want to return a valid texture
    /// \return The currently active texture
    ImageBuffer& AnimatedTexture::get_texture()
    {
        // TODO: What if an ImageBuffer* in this->_textures is dangling or nullptr (which it should not be!) Do we really want to segfault?
        return *this->_textures[this->_current_texture_index];
    }

    void AnimatedTexture::update(int delta_time)
    {
        this->_time_since_last_texture_switch += delta_time;

        if (this->_time_since_last_texture_switch >= this->_get_current_texture_active_time()) {
            this->_select_next_texture();
            this->_time_since_last_texture_switch = 0;
        }
    }

    void AnimatedTexture::_select_next_texture()
    {
        this->_current_texture_index++;
        this->_current_texture_index = this->_current_texture_index % this->_textures.size();
    }

    size_t AnimatedTexture::_get_current_texture_active_time()
    {
        return this->_texture_active_times[this->_current_texture_index];
    }

    size_t AnimatedTexture::get_texture_width()
    {
        return this->_tex_width;
    }

    size_t AnimatedTexture::get_texture_height()
    {
        return this->_tex_height;
    }
}