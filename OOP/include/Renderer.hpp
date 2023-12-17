#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer(){};
    virtual void print_figure(){};
protected:
    sf::RenderWindow* window_p;
};
