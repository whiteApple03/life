#include <SFML/Graphics.hpp>
#include <iostream>

#include "./include/Home_window_controlling.hpp"
#include "./include/Map_renderer.hpp"

int main()
{
    int window_x = 1000;
    int window_y = 1000;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "SFML");
    Map_renderer game{window, window_x, window_y};
    Home_window_controlling control;
    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            control.Map_controlling(event);
            control.menu_controlling(event);
            game.check_resized(event);
        };
        control.auto_change();
    }
    return 0;
}