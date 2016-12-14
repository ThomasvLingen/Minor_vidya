#include "RapidXMLAdapter.hpp"
#include "../exceptions/FileInvalidException.hpp"

using Exceptions::FileInvalidException;

namespace GameLogic {

    RapidXMLAdapter::RapidXMLAdapter()
    {
        this->_doc = new xml_document<>;
    }

    RapidXMLAdapter::~RapidXMLAdapter()
    {
        delete this->_doc;
    }

    /// \brief Set-up of RapidXML xml_document and xml_nodes
    /// 
    /// This function prepares one xml_documents and several nodes that need to exist in the .tmx file
    ///
    /// \param file_location location of the file to be used
    void RapidXMLAdapter::setup_document( string file_location )
    {
        //clear xml document before setup
        this->_doc->clear();
        std::ifstream the_file( file_location );
        if ( the_file.is_open() ) {
            this->_buffer = vector<char>( ( std::istreambuf_iterator<char>( the_file ) ), std::istreambuf_iterator<char>() );
            // if we don't append '\0' rapidxml throws parse_exception
            this->_buffer.push_back( '\0' );
            this->_doc->parse<0>( &_buffer[0] );

            // setup main node map
            this->_map_node = this->_doc->first_node( "map" );
            if ( this->_map_node == 0 ) {
                throw FileInvalidException();
            }
            // setup tileset node
            this->_tileset_node = this->_map_node->first_node( "tileset" );
            if ( this->_tileset_node == 0 ) {
                throw FileInvalidException();
            }
            // setup tileset->image node
            this->_image_node = this->_tileset_node->first_node( "image" );
            if ( this->_image_node == 0 ) {
                throw FileInvalidException();
            }
            // setup layer node
            this->_layer_node = this->_map_node->first_node( "layer" );
            if ( this->_layer_node == 0 ) {
                throw FileInvalidException();
            }
            // setup layer->data node
            this->_data_node = this->_layer_node->first_node( "data" );
            if ( this->_data_node == 0 ) {
                throw FileInvalidException();
            }
            // setup objectgroup node
            this->_object_group_node = this->_map_node->first_node( "objectgroup" );
            if ( this->_object_group_node == 0 ) {
                throw FileInvalidException();
            }
        }
        else {
            throw FileInvalidException();
        }
    }

    /// \brief gets the texture source from loaded .tmx
    /// 
    /// This function returns the source location of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    string RapidXMLAdapter::get_texture_source()
    {
        return this->_image_node->first_attribute( "source" )->value();
    }

    /// \brief gets the texture tile height from loaded .tmx
    /// 
    /// This function returns the texture tile height of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_tile_height()
    {
        this->_tile_height = std::stoi( this->_tileset_node->first_attribute( "tileheight" )->value() );
        return _tile_height;
    }

    /// \brief gets the texture tile width from loaded .tmx
    /// 
    /// This function returns the texture tile width of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_tile_width()
    {
        this->_tile_width = std::stoi( this->_tileset_node->first_attribute( "tilewidth" )->value() );
        return _tile_width;
    }

    /// \brief gets the texture tile count from loaded .tmx
    /// 
    /// This function returns the texture tile count of the texture that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    size_t RapidXMLAdapter::get_tile_count()
    {
        return std::stoi( this->_tileset_node->first_attribute( "tilecount" )->value() );
    }

    /// \brief gets the texture valued map from loaded .tmx
    /// 
    /// This function returns the texture valued map that is used in this .tmx.
    /// RapidXMLAdapter::setup_document has to be called before using this 
    vector<vector<size_t>> RapidXMLAdapter::get_map()
    {
        vector<vector<size_t>> map;
        char* data_value = this->_data_node->value();
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
    /// This should be called as the last step of parsing the .tmx
    vector<tuple<size_t, size_t, char*>> RapidXMLAdapter::get_objects()
    {
        vector<tuple<size_t, size_t, char*>> object_list;
        for ( xml_node<> * object_node = this->_object_group_node->first_node( "object" ); object_node; object_node = object_node->next_sibling() ) {
            size_t x = std::stoi( object_node->first_attribute( "x" )->value() ) / this->_tile_width;
            size_t y = std::stoi( object_node->first_attribute( "y" )->value() ) / this->_tile_height;
            char* type = object_node->first_attribute( "type" )->value();
            tuple<size_t, size_t, char*> object( x, y, type );
            object_list.push_back( object );
        }
        return object_list;
    }


    string RapidXMLAdapter::get_entity_texture( size_t x, size_t y )
    {
        for ( xml_node<> * object_node = this->_object_group_node->first_node( "object" ); object_node; object_node = object_node->next_sibling() ) {
            if ( std::stoi( object_node->first_attribute( "x" )->value() ) / this->_tile_width == x &&  std::stoi( object_node->first_attribute( "y" )->value() ) / this->_tile_height == y) {
                xml_node<> * property_texture = object_node->first_node( "properties" )->first_node( "property" );
                return property_texture->first_attribute( "value" )->value();
            }
        }

        // TODO: Add exception, since this point should not be reached
    }
}