#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <vector>
#include <map>
#include "Color.hpp"
#include "../SDLFacade.hpp"
#include "../../gamelogic/TileTrigger.hpp"

namespace Engine {
    using std::vector;
    using std::string;
    using std::map;

    class TileObject {

    private:
        bool _wall;
        const int _width = 1;        // TODO: implement width value
        const int _length = 1;        // TODO: implement height value

        ImageBuffer* _texture;

    public:
        TileObject(ImageBuffer* texture);
        TileObject(const TileObject& obj) = delete;            // Copy constructor for a base class has to be deleted (slicing)
        TileObject& operator=(const TileObject& obj) = delete; // Copy assignment for a base class has to be deleted (slicing)
        virtual ~TileObject();

        virtual void update(int delta_time);

        void set_wall(bool has_wall);

        void set_texture(ImageBuffer* texture);

        bool is_wall();

        ImageBuffer* get_texture();

    };
}

#endif // !TILEOBJECT_HPP



