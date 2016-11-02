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

    void Raycasting::draw()
    {

        for (int ray_index = 0; ray_index < this->_SDL_facade.get_width(); ray_index++) {
            DoubleCoordinate ray_position = _get_ray_pos();
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

    /// \brief calculates the ray direction using screen width and current ray index
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

    CoordinateInt Raycasting::_get_map_coord(DoubleCoordinate ray_position)
    {
        CoordinateInt map_cord;

        map_cord.x = (int)ray_position.x;
        map_cord.y = (int)ray_position.y;

        return map_cord;
    }

    RaySteps Raycasting::_calculate_ray_steps(Direction ray_dir, DoubleCoordinate ray_pos, CoordinateInt map_coord,
                                              DeltaDist delta_dist)
    {
        RaySteps ray_steps;
        ray_steps.x = _calculate_single_step(ray_dir.x, ray_pos.x, map_coord.x, delta_dist.x);
        ray_steps.y = _calculate_single_step(ray_dir.y, ray_pos.y, map_coord.y, delta_dist.y);

        return ray_steps;
    }

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

    int Raycasting::_get_wall_height(Wall wall, DoubleCoordinate ray_pos, Direction ray_direction, RaySteps ray_steps)
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

    double Raycasting::_calculate_wall_dist(int &wall_cord, double &ray_pos, RayStep ray_step, double ray_dir)
    {
        return (wall_cord - ray_pos + (1 - ray_step.step_size) / 2) / ray_dir;
    }

    LineCords Raycasting::_get_line_measures(int line_height)
    {
        LineCords line;
        int screen_height = this->_SDL_facade.get_height();

        line.draw_start = -line_height / 2 + screen_height / 2;
        if (line.draw_start < 0) {
            line.draw_start = 0;
        }
        line.draw_end = line_height / 2 + screen_height / 2;
        if (line.draw_end >= screen_height) {
            line.draw_end = screen_height - 1;
        }

        return line;
    }

    DoubleCoordinate Raycasting::_get_ray_pos()
    {
        return this->_world->get_pov().get_position();
    }

    void Raycasting::_draw_line(LineCords &line_cords, Color &color, int current_ray_index)
    {
        this->_SDL_facade.draw_line(current_ray_index, line_cords.draw_start, current_ray_index,
                                    line_cords.draw_end, &color);
        //todo color is currently a pointer, but will be changed to a reference, if seg fault, look here
    }
}
