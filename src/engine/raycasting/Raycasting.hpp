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

    class Raycasting {
    public:
        Raycasting(SDLFacade& SDL_facade);

        void handle_input(/* TODO:  Input data type from SDL facade */);
        void update(int delta_time);
        void draw();

        void set_world(WorldPTR new_world);

    private:
        SDLFacade& _SDL_facade;
        WorldPTR _world;

        void _draw_walls(CoordinateDouble& ray_position, vector<double>& distance_buffer);
        void _draw_entities(CoordinateDouble& ray_position, vector<double>& distance_buffer);

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

        double _get_distance_to_ray(Entity& entity, CoordinateDouble ray_pos);

        CoordinateDouble _transform_relative_to_camera_matrix(CoordinateDouble& position);
        vector<Entity*> _get_sorted_entities(CoordinateDouble& ray_position);
        bool _sprite_should_be_drawn(CoordinateDouble& sprite_coords, int sprite_ray_index, vector<double>& distance_buffer);
    };
}


#endif //MINOR_VIDYA_RAYCASTING_HPP
