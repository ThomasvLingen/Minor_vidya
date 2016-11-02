//
// Created by mafn on 11/1/16.
//

#include "Raycasting.hpp"

namespace Engine {

    Raycasting::Raycasting()
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
        int width  /* SDL_Facade get screen width  */;
        int height /* SDL_Facade get screen height */;

        for (int x = 0; x < width; x++) {
            CoordinateDouble ray_position = _get_ray_pos(); /* [World get PoV position] */
            Direction ray_dir = _get_ray_direction(width, x);
            CoordinateInt map_coord = _get_map_coord(ray_position);

            DeltaDist delta_dist = _get_delta_dist(ray_dir);
            RaySteps ray_steps = _calculate_ray_steps(ray_dir, ray_position, map_coord, delta_dist);

            Wall wall = _search_wall(ray_steps, map_coord, delta_dist);
            int line_height = _get_wall_height(wall, ray_position, ray_dir, height, ray_steps);
            LineCords line_cords = _get_line_measures(height, line_height);

            // Somehow determine color to draw (Do something with world)
            if (wall.side == WallSide::y_wall) {
                // Reduce the determined color
            }
            // Draw the line: draw_start, draw_end at x=x
        }
        // Draw the world through raycasting algorithms,
        // For this we need to get information from the world (Like the tile map
        // For this we also need the SDL_Facade to draw
    }

    DeltaDist Raycasting::_get_delta_dist(Direction ray_dir)
    {
        DeltaDist dist;

        dist.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
        dist.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));

        return dist;
    }

    Direction Raycasting::_get_ray_direction(int max_width, int current_width)
    {
        Direction ray_dir;

        double camera_x = 2 * current_width / double(max_width) - 1;
        ray_dir.x /* [World get PoV direction x] + [plane_x] * camera_x */ ;
        ray_dir.y /* [World get PoV direction y] + [plane_y] * camera_x */ ;

        return ray_dir;
    }

    CoordinateInt Raycasting::_get_map_coord(CoordinateDouble ray_position)
    {
        CoordinateInt map_cord;

        map_cord.x = (int)ray_position.x;
        map_cord.y = (int)ray_position.y;

        return map_cord;
    }

    RaySteps Raycasting::_calculate_ray_steps(Direction ray_dir, CoordinateDouble ray_pos, CoordinateInt map_coord,
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

//            if(this->world[start_point.x][start_point.y] > 0){
                break;
//            }
        }

        return_wall.cord = {
            start_point.x,
            start_point.y
        };

        return_wall.side = side;

        return return_wall;
    }

    int Raycasting::_get_wall_height(Wall wall, CoordinateDouble ray_pos, Direction ray_direction, int height,
                                     RaySteps ray_steps)
    {
        double perp_wall_dist;
        int line_height;

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

    LineCords Raycasting::_get_line_measures(int screen_height, int line_height)
    {
        LineCords line;

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

    CoordinateDouble Raycasting::_get_ray_pos()
    {
        CoordinateDouble ray_pos;
        return ray_pos;
    }
}
