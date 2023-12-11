#pragma once
#include <SFML/Graphics.hpp>

struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};

class Map_config {
public:
    int window_x;
    int window_y;
    float size_cell;
    double margin = 0.1;
    sf::RenderWindow* window_p;
    sf::RenderWindow* window_settings;
    int* live_cell_sum;
    Field_t field;
    // Settings settings;
    bool input_mode;
    bool game_mode;
    bool settings_mode;
    bool is_resized = false;
    float offsetX;
    float offsetY;
    bool auto_change = false;
    int delay_between_changed_generations = 100;
    int64_t cur_time;
};