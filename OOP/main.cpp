#include <SFML/Graphics.hpp>
#include <iostream>

#include "./include/Controlling.hpp"
#include "./include/Map_renderer.hpp"

class Input {};

int main()
{
    int window_x = 1000;
    int window_y = 1000;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "SFML");
    Map_renderer map{window, window_x, window_y};
    Home_window_controlling control;

    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            map.check_resized(event);
            control.menu_controlling(event);
        };
        control.Map_controlling(event);
    }
}