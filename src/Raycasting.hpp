//
// Created by mafn on 11/1/16.
//

#ifndef MINOR_VIDYA_RAYCASTING_HPP
#define MINOR_VIDYA_RAYCASTING_HPP

#include <cmath>
#include "RayCastingTypes.hpp"

namespace Engine {
    class Raycasting {
    public:
        Raycasting(/* Either pass a world or create it in the constructor */);
        virtual ~Raycasting();

        void handle_input(/* Input data type from SDL facade */);
        void update(int delta_time);
        void draw();


    private:
        DeltaDist _get_delta_dist(Direction ray_dir);
        CoordinateDouble _get_ray_pos();
        Direction _get_ray_direction(int max_width, int current_width);
        CoordinateInt _get_map_coord(CoordinateDouble ray_position);
        RaySteps _calculate_ray_steps(Direction ray_dir, CoordinateDouble ray_pos, CoordinateInt map_coord,
                                      DeltaDist delta_dist);
        RayStep _calculate_single_step(double &ray_direction, double &ray_position, int &map_position, double &delta_dist);
        Wall _search_wall(RaySteps step_sizes, CoordinateInt start_point, DeltaDist delta_dist);
        int _get_wall_height(Wall wall, CoordinateDouble ray_pos, Direction ray_direction, int height, RaySteps ray_steps);
        double _calculate_wall_dist(int& wall_cord, double& ray_pos, RayStep ray_step, double ray_dir);
        LineCords _get_line_measures(int screen_height, int line_height);
        // Reference (of smart pointer) naar een world
        // Reference (of smart pointer) naar de SDLAdapter / facade
    };
}


#endif //MINOR_VIDYA_RAYCASTING_HPP
