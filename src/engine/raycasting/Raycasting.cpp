//
// Created by mafn on 11/1/16.
//

#include "Raycasting.hpp"

namespace Engine {

    Raycasting::Raycasting(SDLFacade& SDL_facade)
    : _SDL_facade(SDL_facade)
    , _world(nullptr)
    {

    }

    /// \brief Get pressed keys from SDL_facade and parse it to the worldInterface
    void Raycasting::handle_input()
    {
        this->_world->handle_input(this->_SDL_facade.get_input());

        // If we need to do something on a keystroke, handle input ourselves
    }

    /// \brief Call the update on the worldinterface
    void Raycasting::update(int delta_time)
    {
        this->_world->update(delta_time);
    }

    /// \brief Draws a single frame with raycasting using the world object and SDL facade
    void Raycasting::draw()
    {
        if (this->_world != nullptr) {
            this->_SDL_facade.lock_screen_buffer();

            // This is the ZBuffer for the entities to draw
            vector<double> distance_buffer((size_t)this->_SDL_facade.get_width());
            // Things that don't change within a frame can be calculated here
            CoordinateDouble ray_position = this->_get_ray_pos();

            this->_draw_walls(ray_position, distance_buffer);
            this->_draw_entities(ray_position, distance_buffer);

            this->_SDL_facade.unlock_screen_buffer();
            this->_SDL_facade.update_screen_buffer();
        }
    }

    void Raycasting::_draw_walls(CoordinateDouble& ray_position, vector<double>& distance_buffer)
    {
        int screen_height_calc = this->_SDL_facade.get_height() * 128;
        CoordinateInt map_coord = this->_get_map_coord(ray_position);

        for (int ray_index = 0; ray_index < this->_SDL_facade.get_width(); ray_index++) {
            Direction ray_dir = _calculate_ray_direction(ray_index);

            DeltaDist delta_dist = _calculate_delta_distance(ray_dir);
            RaySteps ray_steps = _calculate_ray_steps(ray_dir, ray_position, map_coord, delta_dist);

            Wall wall = _search_wall(ray_steps, map_coord, delta_dist);
            double perp_wall_dist = this->_calculate_wall_dist(wall, ray_position, ray_steps, ray_dir);
            distance_buffer[ray_index] = perp_wall_dist;

            int line_height = _get_wall_height(perp_wall_dist);
            int line_height_calc = line_height * 128;
            LineCords line_cords = _get_line_measures(line_height);

            int tex_x = this->_get_texture_x_coord(wall, ray_position, ray_dir, perp_wall_dist);

            ImageBuffer& tile_texture = *this->_world->get_tile(wall.cord)->get_texture();

            // TODO: Maybe put this in a separate function
            // Put pixels for a single vertical line on the screen
            for (int y = line_cords.draw_start; y < line_cords.draw_end; y++) {
                // The multiplication and division is done so that we don't have to work with floats here, resulting
                // in much faster code. This is critical, since this tidbit of code is ran width * height times PER
                // FRAME (640*480 equates to 307,200 times, which is a lot).
                int d = y * 256 - screen_height_calc + line_height_calc;
                int tex_y = ((d * TEXTURE_HEIGHT) / line_height) / 256;

                Uint32 pixel = tile_texture[TEXTURE_HEIGHT * tex_y + tex_x];

                this->_SDL_facade.draw_pixel_screen_buffer({ray_index, y}, pixel);
            }
        }
    }


    void Raycasting::_draw_entities(CoordinateDouble& ray_position, vector<double>& distance_buffer)
    {
        // The multiplication and division with these factors is done so that we don't have to work with floats here,
        // resulting in much faster code. This is critical, since this tidbit of code is **potentially** ran
        // width * height times PER FRAME (640*480 equates to 307,200 times, which is a lot).
        const int AVOID_FLOAT = 256;
        const int AVOID_FLOAT_HALF = 128;

        // Draw drawables
        vector<Entity*> sorted_entities = this->_get_sorted_entities(ray_position);

        int width = this->_SDL_facade.get_width();
        int height = this->_SDL_facade.get_height();

        for (Entity* entity : sorted_entities) {
            // translate sprite position to relative to camera
            CoordinateDouble sprite_pos = entity->get_position() - ray_position;
            CoordinateDouble transformed = this->_transform_relative_to_camera_matrix(sprite_pos);
            ImageBuffer& entity_texture = *entity->get_texture(); // TODO: place this somewhere it should be (I don't know were and it was a raycasting engine mistake)

            int sprite_screen_x = int((width / 2) * (1 + transformed.x / transformed.y));

            // calculate height of the sprite on screen
            int sprite_length = abs(int(height / (transformed.y))); //using "transform_y" instead of the real distance prevents fisheye
            // calculate lowest and highest pixel to fill in current stripe
            LineCords draw_coords = this->_get_line_measures(sprite_length);

            // calculate width of the sprite
            LineCords sprite_x = this->_get_sprite_horizontal_measures(sprite_length, sprite_screen_x);

            // loop through every vertical stripe of the sprite on screen
            for (int stripe = sprite_x.draw_start; stripe < sprite_x.draw_end; stripe++) {
                // TODO: there is quite a bit of room to be optimised here, certain calculations can be moved a scope higher
                int tex_x = int(AVOID_FLOAT * (stripe - (-sprite_length / 2 + sprite_screen_x)) * TEXTURE_WIDTH / sprite_length) / AVOID_FLOAT;

                if (this->_sprite_should_be_drawn(transformed, stripe, distance_buffer)) {
                    for (int y = draw_coords.draw_start; y < draw_coords.draw_end; y++) {  // for every pixel of the current stripe
                        int unscaled_tex_y = (y) * AVOID_FLOAT - height * AVOID_FLOAT_HALF + sprite_length * AVOID_FLOAT_HALF; // 256 and 128 factors to avoid floats
                        int tex_y = ((unscaled_tex_y * TEXTURE_HEIGHT) / sprite_length) / AVOID_FLOAT;

                        Uint32 pixel = entity_texture[TEXTURE_WIDTH * tex_y + tex_x]; // get current pixel from the texture

                        // TODO: Transparency is done here. There is undoubtedly a better way to do this
                        if ((pixel & 0x000000FF) == 0xFF) {
                            this->_SDL_facade.draw_pixel_screen_buffer({stripe, y}, pixel); // paint pixel if it isn't black, black is the invisible pixel
                        }
                    }
                }
            }
        }
    }

    /// \brief Calculates the distance until the next horizontal and vertical axis.
    ///
    /// Calculates the distance needed to jump from one axis to the next using the current direction
    /// \param ray_dir the direction vector of the "ray"
    /// \return distance for x and y in DeltaDist struct
    DeltaDist Raycasting::_calculate_delta_distance(Direction ray_dir)
    {
        DeltaDist dist;

        dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
        dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));

        return dist;
    }

    /// \brief Calculates the ray direction using screen width and current ray index
    ///
    /// \param max_width current screen width
    /// \param current_ray_index current ray index
    /// \return Direction vector of the ray
    Direction Raycasting::_calculate_ray_direction(int current_ray_index)
    {
        Direction ray_dir;
        int max_width = this->_SDL_facade.get_width();

        double camera_x = 2 * current_ray_index / double(max_width) - 1;
        Direction PoV_direction = this->_world->get_pov().get_direction();
        RaycastingVector PoV_plane = this->_world->get_pov().get_camera_plane();

        ray_dir.x = PoV_direction.x + (PoV_plane.x * camera_x);
        ray_dir.y = PoV_direction.y + (PoV_plane.y * camera_x);

        return ray_dir;
    }


    /// \brief Converts DoubleCoordinate to CoordinateInt
    ///
    /// Converts DoubleCoordinate to CoordinateInt, used to convert ray position to a map coordinate
    /// \param ray_position current ray position
    /// \return ray position in map coordinate
    CoordinateInt Raycasting::_get_map_coord(CoordinateDouble ray_position)
    {
        CoordinateInt map_cord;

        map_cord.x = (int)ray_position.x;
        map_cord.y = (int)ray_position.y;

        return map_cord;
    }


    /// \brief Calculates the ray step size for x and y
    ///
    /// Calculates the ray step size for x and y by calling _calculate_single_step for each
    /// \param ray_dir Ray direction
    /// \param ray_pos Current Ray position
    /// \param map_coord Current map coordinate
    /// \param delta_dist Delta distance for both x and y
    /// \return RaySteps struct containing the stepsize for x and y
    RaySteps Raycasting::_calculate_ray_steps(Direction ray_dir, CoordinateDouble ray_pos, CoordinateInt map_coord,
                                              DeltaDist delta_dist)
    {
        RaySteps ray_steps;
        ray_steps.x = _calculate_single_step(ray_dir.x, ray_pos.x, map_coord.x, delta_dist.x);
        ray_steps.y = _calculate_single_step(ray_dir.y, ray_pos.y, map_coord.y, delta_dist.y);

        return ray_steps;
    }

    /// \brief Calculates the ray step size for a single axis
    ///
    /// Calculates the ray step size for a single axis
    /// \param ray_direction
    /// \param ray_position
    /// \param map_position
    /// \param delta_dist
    /// \return ray step size
    RayStep Raycasting::_calculate_single_step(double& ray_direction, double& ray_position, int& map_position,
                                               double& delta_dist)
    {
        RayStep return_step;
        double delta_length;

        if (ray_direction < 0) {
            return_step.step_size = -1;
            delta_length = ray_position - map_position;
        } else {
            return_step.step_size = 1;
            delta_length = map_position + 1.0 - ray_position;
        }

        return_step.side_distance = delta_length * delta_dist;

        return return_step;
    }

    /// \brief Searches for the next wall using a ray starting from a point
    ///
    /// Searches for the next wall using a ray, ray takes steps of stepsize until it finds a tile with a wall \n
    /// \param step_sizes Ray step size
    /// \param start_point
    /// \param delta_dist
    /// \return Wall struct with location and type of wall (x or y)
    Wall Raycasting::_search_wall(RaySteps step_sizes, CoordinateInt start_point, DeltaDist delta_dist)
    {
        WallSide side;
        Wall return_wall;

        while (true) {
            if (step_sizes.x.side_distance < step_sizes.y.side_distance) {
                step_sizes.x.side_distance += delta_dist.x;
                start_point.x += step_sizes.x.step_size;
                side = WallSide::x_wall;
            } else {
                step_sizes.y.side_distance += delta_dist.y;
                start_point.y += step_sizes.y.step_size;
                side = WallSide::y_wall;
            }

            if (this->_world->get_tile(start_point)->is_wall()) {
                break;
            }
        }

        return_wall.cord = {
            start_point.x,
            start_point.y
        };

        return_wall.side = side;

        return return_wall;
    }

    /// \brief Calculates wall_height using wall / ray position and direction using _calculate_wall_dist
    /// \param perp_wall_dist The distance to a wall
    /// \return wall height
    int Raycasting::_get_wall_height(double perp_wall_dist)
    {
        int height = this->_SDL_facade.get_height();

        return (int)(height / perp_wall_dist);
    }

    /// \brief Calculate the distance to the wall for an axis
    /// \param wall_cord wall position
    /// \param ray_pos ray position
    /// \param ray_step ray step size
    /// \param ray_dir ray direction
    /// \return distance to wall in a double
    double Raycasting::_calculate_wall_dist(int& wall_cord, double& ray_pos, RayStep ray_step, double ray_dir)
    {
        return (wall_cord - ray_pos + (1 - ray_step.step_size) / 2) / ray_dir;
    }

    double Raycasting::_calculate_wall_dist(Wall wall, CoordinateDouble ray_pos, RaySteps ray_steps, Direction ray_dir)
    {
        if (wall.side == WallSide::x_wall) {
            return this->_calculate_wall_dist(wall.cord.x, ray_pos.x, ray_steps.x, ray_dir.x);
        } else {
            return this->_calculate_wall_dist(wall.cord.y, ray_pos.y, ray_steps.y, ray_dir.y);
        };
    }

    /// \brief get line measure from line_height
    /// \param line_height
    /// \return line measure in LineCords
    LineCords Raycasting::_get_line_measures(int line_height)
    {
        LineCords line;
        int screen_height = this->_SDL_facade.get_height();

        line.draw_start = -line_height / 2 + screen_height / 2;
        line.draw_end = line_height / 2 + screen_height / 2;

        this->_correct_line(line, screen_height);

        return line;
    }

    /// \brief Corrects lineCords if out if screen range
    /// \param LineCords containing the line coordinates
    /// \param max_axis_value max value for the corrected line
    void Raycasting::_correct_line(LineCords& line, int max_axis_value)
    {
        if (line.draw_end < 0) {
            line.draw_end = 0;
        }
        if (line.draw_end >= max_axis_value) {
            line.draw_end = max_axis_value - 1;
        }

        if (line.draw_start < 0) {
            line.draw_start = 0;
        }
        if (line.draw_start >= max_axis_value) {
            line.draw_start = max_axis_value - 1;
        }
    }

    CoordinateDouble Raycasting::_get_ray_pos()
    {
        return this->_world->get_pov().get_position();
    }

    void Raycasting::set_world(WorldPTR new_world)
    {
        this->_world = new_world;
    }

    int Raycasting::_get_texture_x_coord(Wall wall, CoordinateDouble ray_pos, Direction ray_dir, double perp_wall_dist)
    {
        double wall_x = this->_get_wall_x(wall, ray_pos, ray_dir, perp_wall_dist);

        // x coordinate on the texture
        int tex_x = int(wall_x * double(TEXTURE_WIDTH));

        if ((wall.side == WallSide::x_wall && ray_dir.x > 0) || (wall.side == WallSide::y_wall && ray_dir.y < 0)) {
            tex_x = TEXTURE_WIDTH - tex_x - 1;
        }

        return tex_x;
    }

    double Raycasting::_get_wall_x(Wall wall, CoordinateDouble ray_pos, Direction ray_dir, double perp_wall_dist)
    {
        double wall_x;

        if (wall.side == WallSide::x_wall) {
            wall_x = ray_pos.y + perp_wall_dist * ray_dir.y;
        } else {
            wall_x = ray_pos.x + perp_wall_dist * ray_dir.x;
        }

        wall_x -= floor(wall_x);

        return wall_x;
    }

    LineCords Raycasting::_get_sprite_horizontal_measures(int sprite_width, int sprite_screen_x)
    {
        LineCords line;

        line.draw_start = -sprite_width / 2 + sprite_screen_x;
        line.draw_end = sprite_width / 2 + sprite_screen_x;

        this->_correct_line(line, this->_SDL_facade.get_width());

        return line;
    }

    double Raycasting::_get_distance_to_ray(Entity& entity, CoordinateDouble ray_pos)
    {
        double delta_x = ray_pos.x - entity.get_position().x;
        double delta_y = ray_pos.y - entity.get_position().y;

        return pow(delta_x, 2) + pow(delta_y, 2);
    }

    CoordinateDouble Raycasting::_transform_relative_to_camera_matrix(CoordinateDouble& position)
    {
        // transform sprite with the inverse camera matrix
        // [ plane_x   dir_x ] -1                                       [ dir_y      -dir_x ]
        // [                 ]   =  1/(plane_x*dir_y-dir_x*plane_y) *   [                   ]
        // [ plane_y   dir_y ]                                          [ -plane_y  plane_x ]

        Direction& dir = this->_world->get_pov().get_direction();
        RaycastingVector& PoV_plane = this->_world->get_pov().get_camera_plane();

        double inv_det = 1.0 / (PoV_plane.x * dir.y - dir.x * PoV_plane.y); // required for correct matrix multiplication
        return CoordinateDouble {
            inv_det * (dir.y * position.x - dir.x * position.y),
            inv_det * (-PoV_plane.y * position.x + PoV_plane.x * position.y)
        };
    }

    vector<Entity*> Raycasting::_get_sorted_entities(CoordinateDouble& ray_position)
    {
        // TODO: This is copied, but we might not have to. Does order of enemies matter for anything else?
        vector<Entity*> sorted_entities = this->_world->get_entities();

        std::sort(
            sorted_entities.begin(), sorted_entities.end(),
            [ray_position, this] (Entity* a, Entity* b) {
                return this->_get_distance_to_ray(*a, ray_position) > this->_get_distance_to_ray(*b, ray_position);
            }
        );

        return sorted_entities;
    }

    bool Raycasting::_sprite_should_be_drawn(CoordinateDouble& sprite_coords, int sprite_ray_index, vector<double>& distance_buffer)
    {
        bool in_front_of_camera = sprite_coords.y > 0;
        bool within_screen_bounds = sprite_ray_index > 0 && sprite_ray_index < this->_SDL_facade.get_width();
        bool no_wall_between = sprite_coords.y < distance_buffer[sprite_ray_index];

        return in_front_of_camera && within_screen_bounds && no_wall_between;
    }
}
