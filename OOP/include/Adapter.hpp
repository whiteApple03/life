#pragma once
#include <SFML/Graphics.hpp>

#include "../configurate/map_config.hpp"

// extern Map_config map_config;

class Adapter : public Storage {
protected:
    void calculate_cell_size()
    {
        float X = (map_config.window_x - map_config.window_x * map_config.margin * 2.)
                / map_config.field.sizeX;
        float Y = (map_config.window_y - map_config.window_y * map_config.margin * 2.)
                / map_config.field.sizeY;
        map_config.size_cell = (X < Y) ? X : Y;
        calc_offsets();
    }
    void calc_offsets()
    {
        map_config.offsetX
                = (map_config.window_x - map_config.field.sizeX * map_config.size_cell) / 2.;
        map_config.offsetY
                = (map_config.window_y - map_config.field.sizeY * map_config.size_cell) / 2.;
    }
};