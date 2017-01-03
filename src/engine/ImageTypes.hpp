//
// Created by wouter on 12/12/16.
//

#ifndef MINOR_VIDYA_IMAGETYPES_H
#define MINOR_VIDYA_IMAGETYPES_H

#include <vector>
#include <map>
#include <string>

namespace Engine {
    using std::vector;
    using std::map;
    using std::string;

    typedef vector<uint32_t> ImageBuffer;
    typedef map<int, ImageBuffer*> TextureMap;

    // Animation name --> Animation textures
    typedef map<string, vector<ImageBuffer*>> AnimationTextureMap;
}

#endif //MINOR_VIDYA_IMAGETYPES_H
