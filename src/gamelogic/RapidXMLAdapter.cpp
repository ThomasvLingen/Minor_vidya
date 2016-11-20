#include "RapidXMLAdapter.hpp"


namespace GameLogic {

    RapidXMLAdapter::RapidXMLAdapter()
    {
        _doc = new xml_document<>;
    }

    RapidXMLAdapter::~RapidXMLAdapter()
    {
        delete _doc;
        delete _map_node;
    }

    /// \brief Set-up of RapidXML xml_document and xml_nodes
    /// 
    /// This function prepares one xml_documents and several nodes that need to exist in the .tmx file
    ///
    /// \param file_location location of the file to be used
    void RapidXMLAdapter::setup_document( string file_location )
    {
        //clear xml document before setup
        _doc->clear();
        std::ifstream the_file( file_location );
        if ( the_file.is_open() ) {
            _buffer = vector<char>( ( std::istreambuf_iterator<char>( the_file ) ), std::istreambuf_iterator<char>() );
            // if we don't append '\0' rapidxml throws parse_exception
            _buffer.push_back( '\0' );
            _doc->parse<0>( &_buffer[0] );

            // setup main node map
            _map_node = _doc->first_node( "map" );
            if ( _map_node == 0 ) {
                throw exception( "file invalid no TileMap" );
            }
            // setup tileset node
            _tileset_node = _map_node->first_node( "tileset" );
            if ( _tileset_node == 0 ) {
                throw exception( "file invalid no textures" );
            }
            // setup tileset->image node
            _image_node = _tileset_node->first_node( "image" );
            if ( _image_node == 0 ) {
                throw exception( "file invalid no textures" );
            }
            // setup layer node
            _layer_node = _map_node->first_node( "layer" );
            if ( _layer_node == 0 ) {
                throw exception( "file invalid no TileMap" );
            }
            // setup layer->data node
            _data_node = _layer_node->first_node( "data" );
            if ( _data_node == 0 ) {
                throw exception( "file invalid no TileMap" );
            }
            // setup objectgroup node
            _object_group_node = _map_node->first_node( "objectgroup" );
            if ( _object_group_node == 0 ) {
                throw exception( "file invalid no Objects" );
            }
        }
        else {
            throw exception( "can't open file" );
        }
    }

    /// \brief gets the texture source from loaded .tmx
    /// 
    /// This function returns the source location of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    string RapidXMLAdapter::get_texture_source()
    {
        return _image_node->first_attribute( "source" )->value();
    }

    /// \brief gets the texture image height from loaded .tmx
    /// 
    /// This function returns the texture image height of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_image_height()
    {
        return std::stoi( _image_node->first_attribute( "height" )->value() );
    }

    /// \brief gets the texture image width from loaded .tmx
    /// 
    /// This function returns the texture image width of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_image_width()
    {
        return std::stoi( _image_node->first_attribute( "width" )->value() );
    }

    /// \brief gets the texture tile size from loaded .tmx
    /// 
    /// This function returns the texture tile size of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_tile_size()
    {
        size_t tile_height, tile_width;
        tile_height = std::stoi( this->_tileset_node->first_attribute( "tileheight" )->value() );
        tile_width = std::stoi( this->_tileset_node->first_attribute( "tilewidth" )->value() );
        if ( tile_height == tile_width ) {
            return tile_height;
        }
        else {
            throw exception( "file invalid tiles not squares" );
        }
    }

    /// \brief gets the texture valued map from loaded .tmx
    /// 
    /// This function returns the texture valued map that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    vector<vector<size_t>> RapidXMLAdapter::get_map()
    {
        vector<vector<size_t>> map;
        char* data_value = _data_node->value();
        std::stringstream row_ss( data_value );
        string row_chars;

        while ( std::getline( row_ss, row_chars, '\n' ) ) {
            vector<size_t> row_ints;
            std::stringstream char_ss( row_chars );
            string x_y_char;

            while ( std::getline( char_ss, x_y_char, ',' ) ) {
                row_ints.push_back( std::stoi( x_y_char.c_str() ) );
            }
            map.push_back( row_ints );
        }

        return map;
    }

    /// \brief gets the objects from loaded .tmx
    /// 
    /// This function returns the objects that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    vector<tuple<size_t, size_t, char*>> RapidXMLAdapter::get_objects()
    {
        vector<tuple<size_t, size_t, char*>> object_list;
        for ( xml_node<> * object_node = _object_group_node->first_node( "object" ); object_node; object_node = object_node->next_sibling() ) {
            size_t x = std::stoi( object_node->first_attribute( "x" )->value() ) / 64;
            size_t y = std::stoi( object_node->first_attribute( "y" )->value() ) / 64;
            char* type = object_node->first_attribute( "type" )->value();
            tuple<size_t, size_t, char*> object( x, y, type );
            object_list.push_back( object );
        }
        return object_list;
    }
}