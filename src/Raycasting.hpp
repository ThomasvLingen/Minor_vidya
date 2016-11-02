//
// Created by mafn on 11/1/16.
//

#ifndef MINOR_VIDYA_RAYCASTING_HPP
#define MINOR_VIDYA_RAYCASTING_HPP

#include <cmath>
#include <memory>
#include "RayCastingTypes.hpp"
#include "SDLFacade.hpp"
#include "WorldObject.hpp"
#include "DoubleCoordinate.hpp"

namespace Engine {

    using std::shared_ptr;
    typedef shared_ptr<WorldObject> WorldPTR;

    class Raycasting {
    public:
        Raycasting(SDLFacade& SDL_facade, WorldPTR world);
        virtual ~Raycasting();

        void handle_input(/* Input data type from SDL facade */);
        void update(int delta_time);
        void draw();


    private:
        SDLFacade& _SDL_facade;
        WorldPTR _world;
        DeltaDist _calculate_delta_distance(Direction ray_dir);
        DoubleCoordinate _get_ray_pos();
        Direction _calculate_ray_direction(int current_ray_index);
        CoordinateInt _get_map_coord(DoubleCoordinate ray_position);
        RaySteps _calculate_ray_steps(Direction ray_dir, DoubleCoordinate ray_pos, CoordinateInt map_coord,
                                      DeltaDist delta_dist);
        RayStep _calculate_single_step(double &ray_direction, double &ray_position, int &map_position, double &delta_dist);
        Wall _search_wall(RaySteps step_sizes, CoordinateInt start_point, DeltaDist delta_dist);
        int _get_wall_height(Wall wall, DoubleCoordinate ray_pos, Direction ray_direction, RaySteps ray_steps);
        double _calculate_wall_dist(int& wall_cord, double& ray_pos, RayStep ray_step, double ray_dir);
        LineCords _get_line_measures(int line_height);
        void _draw_line(LineCords& line_cords, Color& color, int current_ray_index);
    };
}


#endif //MINOR_VIDYA_RAYCASTING_HPP
