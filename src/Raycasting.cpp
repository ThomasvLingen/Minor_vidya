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
            double camera_x = 2 * x / double(width) - 1;
            double ray_position_x /* [World get PoV position x] */ ;
            double ray_position_y /* [World get PoV position y] */ ;
            double ray_dir_x /* [World get PoV direction x] + [plane_x] * camera_x */ ;
            double ray_dir_y /* [World get PoV direction y] + [plane_y] * camera_x */ ;

            int map_x = int(ray_position_x);
            int map_y = int(ray_position_y);

            double side_dist_x;
            double side_dist_y;

            double delta_dist_x = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
            double delta_dist_y = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
            double perp_wall_dist;

            int step_x;
            int step_y;

            int hit = 0;
            int side;

            if (ray_dir_x < 0) {
                step_x = -1;
                side_dist_x = (ray_position_x - map_x) * delta_dist_x;
            } else {
                step_x = 1;
                side_dist_x = (map_x + 1.0 - ray_position_x) * delta_dist_x;
            }

            if (ray_dir_y < 0) {
                step_y = -1;
                side_dist_y = (ray_position_y - map_y) * delta_dist_y;
            } else {
                step_y = 1;
                side_dist_y = (map_y + 1.0 - ray_position_y) * delta_dist_y;
            }

            while (hit == 0) {
                if (side_dist_x < side_dist_y) {
                    side_dist_x += delta_dist_x;
                    map_x += step_x;
                    side = 0;
                } else {
                    side_dist_y += delta_dist_y;
                    map_y += step_y;
                    side = 1;
                }

                if (/* World check if current_location is a wall */1) {
                    hit = 1;
                }
            }

            if (side == 0) {
                perp_wall_dist = (map_x - ray_position_x + (1 - step_x) / 2) / ray_dir_x;
            } else {
                perp_wall_dist = (map_y - ray_position_y + (1 - step_y) / 2) / ray_dir_y;
            }

            int line_height = (int)(height / perp_wall_dist);

            int draw_start = -line_height / 2 + height / 2;
            if (draw_start < 0) {
                draw_start = 0;
            }
            int draw_end = line_height / 2 + height / 2;
            if (draw_end >= height) {
                draw_end = height - 1;
            }

            // Somehow determine color to draw (Do something with world)
            if (side == 1) {
                // Reduce the determined color
            }
            // Draw the line: draw_start, draw_end at x=x
        }
        // Draw the world through raycasting algorithms,
        // For this we need to get information from the world (Like the tile map
        // For this we also need the SDL_Facade to draw
    }
}
