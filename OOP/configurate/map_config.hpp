#pragma once
#include <SFML/Graphics.hpp>

struct Field_t {
    int sizeX;
    int sizeY;
    bool** field;
};

struct Settings {
    int windowX;
    int windowY;
    int x;
    int y;
    int cur_choise = 0;
    int delay_between_changed_generations = 1000;

    float offsetX;
    float offsetY;
    float margin = 0.1;

    int* order[3] = {&x, &y, &delay_between_changed_generations};
    std::vector<std::string> property
            = {"size map X",
               "size map Y",
               "delay",
               "enter - to chose property and then enter to accept property\ndown, Up - to "
               "control\nM - to accept changes"};
    bool is_changed = false;
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
    Settings settings;
    bool input_mode;
    bool game_mode;
    bool settings_mode;
    bool is_resized = false;
    float offsetX;
    float offsetY;
    bool auto_change = false;
    int delay_between_changed_generations = 1000;
    int64_t cur_time;

    // ~Map_config() {
    //     clear_matrix(field.field, field.sizeY);
    //     delete live_cell_sum;
    //     delete &(settings.order);
    //     delete &(settings.property);
    // }
private:
    // void clear_matrix(bool **a, int n) {
    //     for(int i = 0; i < n; i++) {
    //         delete a[i];
    //     }
    // }
};

class Storage {
public:
    Storage(){};

protected:
    static Map_config map_config;

private:
};
Map_config Storage::map_config;