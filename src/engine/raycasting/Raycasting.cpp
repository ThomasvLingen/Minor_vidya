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
        int screen_height_calc = this->_SDL_facade.get_height() * 128;
        if (this->_world != nullptr) {
            this->_SDL_facade.lock_screen_buffer();

            // Draw walls
            double distance_buffer[_SDL_facade.get_width()];

            for (int ray_index = 0; ray_index < this->_SDL_facade.get_width(); ray_index++) {
                CoordinateDouble ray_position = _get_ray_pos();
                Direction ray_dir = _calculate_ray_direction(ray_index);
                CoordinateInt map_coord = _get_map_coord(ray_position);

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

            // Draw drawables
            // First sort the sprites by distance to the player
            CoordinateDouble ray_pos = this->_get_ray_pos();
            vector<Enemy*> sorted_enemies {this->test_enemies.begin(), this->test_enemies.end()};

            std::sort(
                sorted_enemies.begin(), sorted_enemies.end(),
                [ray_pos] (Enemy* a, Enemy* b) {
                    return a->get_distance_to_point(ray_pos) > b->get_distance_to_point(ray_pos);
                }
            );

            for(Enemy* enemy : sorted_enemies) {
                //translate sprite position to relative to camera
                double spriteX = enemy->x_pos - _get_ray_pos().x;
                double spriteY = enemy->y_pos - _get_ray_pos().y;

                //transform sprite with the inverse camera matrix
                // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
                // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
                // [ planeY   dirY ]                                          [ -planeY  planeX ]

                double dirX = this->_world->get_pov().get_direction().x;
                double dirY = this->_world->get_pov().get_direction().y;

                RaycastingVector PoV_plane = this->_world->get_pov().get_camera_plane();
                double planeX = PoV_plane.x;
                double planeY = PoV_plane.y;
                double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

                double transformX = invDet * (dirY * spriteX - dirX * spriteY);
                double transformY = invDet * (-planeY * spriteX + planeX *
                                                                  spriteY); //this is actually the depth inside the screen, that what Z is in 3D

                int w = _SDL_facade.get_width();
                int h = _SDL_facade.get_height();

                int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

                //calculate height of the sprite on screen
                int spriteHeight = abs(
                        int(h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
                //calculate lowest and highest pixel to fill in current stripe
                int drawStartY = -spriteHeight / 2 + h / 2;
                if (drawStartY < 0) drawStartY = 0;
                int drawEndY = spriteHeight / 2 + h / 2;
                if (drawEndY >= h) drawEndY = h - 1;

                //calculate width of the sprite
                int spriteWidth = abs(int(h / (transformY)));
                int drawStartX = -spriteWidth / 2 + spriteScreenX;
                if (drawStartX < 0) drawStartX = 0;
                int drawEndX = spriteWidth / 2 + spriteScreenX;
                if (drawEndX >= w) drawEndX = w - 1;

                //loop through every vertical stripe of the sprite on screen
                for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
                    int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * TEXTURE_WIDTH / spriteWidth) / 256;
                    //the conditions in the if are:
                    //1) it's in front of camera plane so you don't see things behind you
                    //2) it's on the screen (left)
                    //3) it's on the screen (right)
                    //4) ZBuffer, with perpendicular distance
                    if (transformY > 0 && stripe > 0 && stripe < w && transformY < distance_buffer[stripe])
                        for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
                        {
                            int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
                            int texY = ((d * TEXTURE_HEIGHT) / spriteHeight) / 256;
                            Uint32 color = enemy->texture[TEXTURE_WIDTH * texY + texX]; //get current color from the texture
                            // TODO: Transparency is done here. pls fix
                            if ((color & 0xFFFFFF00) != 0)
                                _SDL_facade.draw_pixel_screen_buffer({stripe, y},
                                                                     color); //paint pixel if it isn't black, black is the invisible color
                        }
                }
            }


            this->_SDL_facade.unlock_screen_buffer();
            this->_SDL_facade.update_screen_buffer();
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

        this->_correct_line(line);

        return line;
    }

    /// \brief Corrects lineCords if out if screen range
    /// \param LineCords containing the line coordinates
    void Raycasting::_correct_line(LineCords& line)
    {
        int screen_height = this->_SDL_facade.get_height();

        if (line.draw_end < 0) {
            line.draw_end = 0;
        }
        if (line.draw_end >= screen_height) {
            line.draw_end = screen_height - 1;
        }

        if (line.draw_start < 0) {
            line.draw_start = 0;
        }
        if (line.draw_start >= screen_height) {
            line.draw_start = screen_height - 1;
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
}
