//
// Created by mafn on 11/1/16.
//

#ifndef MINOR_VIDYA_RAYCASTING_HPP
#define MINOR_VIDYA_RAYCASTING_HPP

#include <cmath>
#include <memory>
#include "RayCastingTypes.hpp"
#include "../SDLFacade.hpp"
#include "../domain/World.hpp"
#include "../domain/CoordinateDouble.hpp"
#include <vector>
#include <algorithm>

namespace Engine {
    using std::shared_ptr;
    typedef shared_ptr<World> WorldPTR;

    // TODO:
    // This is ugly and stupid
    // - Linus Torvalds
    const int TEXTURE_WIDTH = 64;
    const int TEXTURE_HEIGHT = 64;

    // TODO: THIS IS TEMPORARY TESTING CODE
    struct Enemy {
        double x_pos;
        double y_pos;
        ImageBuffer texture;
        Enemy(double newX, double newY, ImageBuffer newTexture){
            this->x_pos = newX;
            this->y_pos = newY;
            this->texture = newTexture;
        }

        inline double get_distance_to_point(CoordinateDouble pos) const
        {
            double delta_x = pos.x - this->x_pos;
            double delta_y = pos.y - this->y_pos;

            // For some reason the sqrt is not needed. wut.
            return pow(delta_x, 2) + pow(delta_y, 2);
        };
    };
    // END TODO

    class Raycasting {
    public:
        Raycasting(SDLFacade& SDL_facade);

        // TODO: THIS IS TEMPORARY TESTING CODE
        vector<Enemy*> test_enemies;
        // END TODO

        void handle_input(/* TODO:  Input data type from SDL facade */);
        void update(int delta_time);
        void draw();

        void set_world(WorldPTR new_world);

    private:
        SDLFacade& _SDL_facade;
        WorldPTR _world;

        void _draw_walls(CoordinateDouble ray_position, double distance_buffer[]);
        void _draw_entities(CoordinateDouble ray_position, double distance_buffer[]);

        DeltaDist _calculate_delta_distance(Direction ray_dir);
        CoordinateDouble _get_ray_pos();
        Direction _calculate_ray_direction(int current_ray_index);
        CoordinateInt _get_map_coord(CoordinateDouble ray_position);

        RaySteps _calculate_ray_steps(Direction ray_dir, CoordinateDouble ray_pos, CoordinateInt map_coord,
                                      DeltaDist delta_dist);
        RayStep _calculate_single_step(double& ray_direction, double& ray_position, int& map_position,
                                       double& delta_dist);

        Wall _search_wall(RaySteps step_sizes, CoordinateInt start_point, DeltaDist delta_dist);
        int _get_wall_height(double perp_wall_dist);
        double _calculate_wall_dist(int& wall_cord, double& ray_pos, RayStep ray_step, double ray_dir);
        double _calculate_wall_dist(Wall wall, CoordinateDouble ray_pos, RaySteps ray_steps, Direction ray_dir);

        LineCords _get_line_measures(int line_height);
        LineCords _get_sprite_horizontal_measures(int sprite_width, int sprite_screen_x);
        void _correct_line(LineCords& line, int max_axis_value);

        int _get_texture_x_coord(Wall wall, CoordinateDouble ray_pos, Direction ray_dir, double perp_wall_dist);
        double _get_wall_x(Wall wall, CoordinateDouble ray_pos, Direction ray_dir, double perp_wall_dist);
    };
}


#endif //MINOR_VIDYA_RAYCASTING_HPP
