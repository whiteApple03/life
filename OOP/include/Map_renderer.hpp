#pragma once

#include "./Adapter.hpp"
#include "./Helper.hpp"
#include "./Renderer.hpp"
#include "Painter.hpp"


class Map_renderer : public Renderer, public Helper, public Adapter, public Painter {
private:    

public:
    Map_renderer(sf::RenderWindow& window, int window_x, int window_y)
    {
        map_config.window_x = window_x;
        map_config.window_y = window_y;
        window_p = &window;
        map_config.window_p = &window;

        window_p->setPosition(sf::Vector2i(0, 0));
        std::cout << window_p << std::endl;

        map_config.field.sizeX = 50;
        map_config.field.sizeY = 50;
        map_config.input_mode = true;
        map_config.game_mode = false;
        map_config.settings_mode = false;

        calculate_cell_size();
        setInputMode();
        allocate_memory_for_field(map_config.field);
        display();
    }
    Map_renderer(sf::RenderWindow& window)
    {
        map_config.window_x = 1000;
        map_config.window_y = 1000;
        window_p = &window;
        map_config.window_p = &window;

        window_p->setPosition(sf::Vector2i(0, 0));

        map_config.field.sizeX = 50;
        map_config.field.sizeY = 50;
        map_config.input_mode = true;
        map_config.game_mode = false;
        map_config.settings_mode = false;

        calculate_cell_size();
        setInputMode();
        allocate_memory_for_field(map_config.field);
        display();
    }

    ~Map_renderer() {
        std::cout << "Distructor Map_renderere : " << map_config.window_p << std::endl;
    }

    void resized(int width, int height)
    {
        sf::FloatRect visiableArea(0, 0, width, height);
        window_p->setView(sf::View(visiableArea));
        map_config.window_x = width;
        map_config.window_y = height;
        calculate_cell_size();
        calc_offsets();
    }

    bool check_resized(sf::Event& event)
    {
        static int width, height;
        if (event.type == sf::Event::Resized) {
            map_config.is_resized = true;
            height = event.size.height;
            width = event.size.width;
            map_config.window_p->clear();
            map_config.window_p->display();
            return true;
        } else if (map_config.is_resized) {
            map_config.is_resized = false;
            resized(width, height);
            display();
            return true;
        }
        return false;
    }


};