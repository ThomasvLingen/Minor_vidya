//
// Created by wouter on 12/12/16.
//

#ifndef MINOR_VIDYA_IMAGETYPES_H
#define MINOR_VIDYA_IMAGETYPES_H

#include <vector>
#include <map>

namespace Engine {
    using std::vector;
    using std::map;

    typedef std::vector<uint32_t> ImageBuffer;
    typedef map<int, ImageBuffer*> TextureMap;
}

#endif //MINOR_VIDYA_IMAGETYPES_H
