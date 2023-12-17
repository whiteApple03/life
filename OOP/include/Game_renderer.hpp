#pragma once
#include <SFML/Graphics.hpp>

#include "Map_renderer.hpp"
#include "Settings_renderer.hpp"

class Game_renderer {
public:
    Game_renderer(sf::RenderWindow& window, int window_x, int window_y)
    {
        map_renderer = new Map_renderer{window, window_x, window_y};
    }

    Map_renderer* map_renderer;
    Settings_renderer* settings_renderer;
};