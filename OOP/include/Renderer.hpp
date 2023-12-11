#pragma once

#include <SFML/Graphics.hpp>
class Renderer {
public:
    Renderer(){};
    virtual void print_figure(){};
    virtual void change_color(sf::Color new_color){};
    virtual void print_text(std::string text, sf::Font font){};
    // virtual sf::RenderWindow& create_window() {};
protected:
    sf::RenderWindow* window_p;
};
