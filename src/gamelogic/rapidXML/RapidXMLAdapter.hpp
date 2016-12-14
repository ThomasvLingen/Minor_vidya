#ifndef RAPIDXMLADAPTER_HPP
#define RAPIDXMLADAPTER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <tuple>
#include "../../../libs/RapidXML/rapidxml.hpp"

namespace GameLogic {
    using std::string;
    using std::vector;
    using std::exception;
    using std::stringstream;
    using std::tuple;

    using rapidxml::xml_node;
    using rapidxml::xml_document;

    class RapidXMLAdapter {
    public:
        RapidXMLAdapter();
        ~RapidXMLAdapter();

        void setup_document( string file_location );

        string get_texture_source();
        size_t get_tile_height();
        size_t get_tile_width();
        size_t get_tile_count();
        vector<vector<size_t>> get_map();
        vector<tuple<size_t, size_t, size_t, char*>> get_objects();
        string get_entity_texture( size_t id);
    private:
        vector<char> _buffer;
        xml_document<>* _doc;
        xml_node<>* _map_node;
        xml_node<>* _tileset_node;
        xml_node<>* _image_node;
        xml_node<>* _layer_node;
        xml_node<>* _data_node;
        xml_node<>* _object_group_node;
        size_t _tile_width;
        size_t _tile_height;
    };
};
#endif // !RAPIDXMLADAPTER_HPP
