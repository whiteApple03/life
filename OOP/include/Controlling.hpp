#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

#include "../configurate/map_config.hpp"
#include "Helper.hpp"
#include "Logic.hpp"
#include "Painter.hpp"
// #include "Settings_renderer.hpp"

extern Map_config map_config;

class Controlling {
    virtual void input_keyboard(sf::Event&){};
};



