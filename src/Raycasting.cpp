//
// Created by mafn on 11/1/16.
//

#include "Raycasting.hpp"

namespace Engine {

    Raycasting::Raycasting(SDLFacade& SDL_facade, WorldPTR world)
    : _SDL_facade(SDL_facade)
    , _world(world)
    {

    }

    Raycasting::~Raycasting()
    {

    }

    void Raycasting::handle_input()
    {
        // Call world handle_input

        // If we need to do something on a keystroke, handle input ourselves
    }

    void Raycasting::update(int delta_time)
    {
        // Call world update
    }

    /// \brief Draws a single frame with raycasting using the world object and SDL facade
    void Raycasting::draw()
    {

        for (int ray_index = 0; ray_index < this->_SDL_facade.get_width(); ray_index++) {
            CoordinateDouble ray_position = _get_ray_pos();
            Direction ray_dir = _calculate_ray_direction(ray_index);
            CoordinateInt map_coord = _get_map_coord(ray_position);

            DeltaDist delta_dist = _calculate_delta_distance(ray_dir);
            RaySteps ray_steps = _calculate_ray_steps(ray_dir, ray_position, map_coord, delta_dist);

            Wall wall = _search_wall(ray_steps, map_coord, delta_dist);
            int line_height = _get_wall_height(wall, ray_position, ray_dir, ray_steps);
            LineCords line_cords = _get_line_measures(line_height);

            Color color = this->_world->get_tile(wall.cord.x, wall.cord.y)->get_color();

//            if (wall.side == WallSide::y_wall) {
//                color = color.reduce_intensity();
//            }

            this->_draw_line(line_cords, color, ray_index);
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
    RayStep Raycasting::_calculate_single_step(double &ray_direction, double &ray_position, int &map_position, double &delta_dist)
    {
        RayStep return_step;
        double delta_length;

        if(ray_direction < 0){
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

        while(true){
            if(step_sizes.x.side_distance < step_sizes.y.side_distance){
                step_sizes.x.side_distance += delta_dist.x;
                start_point.x += step_sizes.x.step_size;
                side = WallSide::x_wall;
            } else {
                step_sizes.y.side_distance += delta_dist.y;
                start_point.y += step_sizes.y.step_size;
                side = WallSide::y_wall;
            }

            if(this->_world->get_tile(start_point.x, start_point.y)->is_wall()){
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
    /// \param wall Wall position
    /// \param ray_pos
    /// \param ray_direction
    /// \param ray_steps
    /// \return wall height
    int Raycasting::_get_wall_height(Wall wall, CoordinateDouble ray_pos, Direction ray_direction, RaySteps ray_steps)
    {
        double perp_wall_dist;
        int line_height;
        int height = this->_SDL_facade.get_height();

        if(wall.side == WallSide::x_wall){
            perp_wall_dist = _calculate_wall_dist(wall.cord.x, ray_pos.x, ray_steps.x, ray_direction.x);
        } else {
            perp_wall_dist = _calculate_wall_dist(wall.cord.y, ray_pos.y, ray_steps.y, ray_direction.y);
        }

        line_height = (int)(height / perp_wall_dist);
        return line_height;
    }

    /// \brief Calculate the distance to the wall for an axis
    /// \param wall_cord wall position
    /// \param ray_pos ray position
    /// \param ray_step ray step size
    /// \param ray_dir ray direction
    /// \return distance to wall in a double
    double Raycasting::_calculate_wall_dist(int &wall_cord, double &ray_pos, RayStep ray_step, double ray_dir)
    {
        return (wall_cord - ray_pos + (1 - ray_step.step_size) / 2) / ray_dir;
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
    void Raycasting::_correct_line(LineCords &line)
    {
        int screen_height = this->_SDL_facade.get_height();

        if(line.draw_end < 0){
            line.draw_end = 0;
        }
        if(line.draw_end >= screen_height){
            line.draw_end = screen_height - 1;
        }

        if(line.draw_start < 0){
            line.draw_start = 0;
        }
        if(line.draw_start >= screen_height){
            line.draw_start = screen_height - 1;
        }
    }

    CoordinateDouble Raycasting::_get_ray_pos()
    {
        return this->_world->get_pov().get_position();
    }

    /// \brief Draws the line using the SDL facade
    /// \param line_cords
    /// \param color
    /// \param current_ray_index
    void Raycasting::_draw_line(LineCords &line_cords, Color &color, int current_ray_index)
    {
        this->_SDL_facade.draw_line(current_ray_index, line_cords.draw_start, current_ray_index,
                                    line_cords.draw_end, &color);
        //todo color is currently a pointer, but will be changed to a reference, if seg fault, look here
    }
}
