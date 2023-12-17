#pragma once 
#include <SFML/Graphics.hpp>

#include "../configurate/map_config.hpp"

// extern Map_config map_config;

class Painter_settings : public Storage {
public:
    void draw_settings()
    {
        sf::Text property_text;
        sf::Text property_value;
        install_font(property_text, 20, "../font/Ubuntu-Regular.ttf");
        install_font(property_value, 20, "../font/Ubuntu-Regular.ttf");
        float offsetX = map_config.settings.offsetX;
        float offsetY = map_config.settings.offsetY;

        int margin = 100;

        for (int i = 0; i < map_config.settings.property.size() - 1; i++) {
            if (map_config.settings.cur_choise == i) {
                draw_property(sf::Color::Blue, i);
            } else {
                draw_property(sf::Color::Black, i);
            }
            int porperty_size = map_config.settings.property.size();
            property_text.setString(map_config.settings.property[porperty_size - 1]);
            property_text.setPosition(sf::Vector2f(
                    map_config.settings.offsetX,
                    map_config.settings.offsetY + 100 * (porperty_size - 1)));
            property_text.setCharacterSize(
                    (map_config.settings.windowX / map_config.settings.property[porperty_size - 1].size())
                    * 2);
            map_config.window_settings->draw(property_text);

            map_config.window_settings->display();
        }
    }
    void install_font(sf::Text& text, int char_size, std::string font_path)
    {
        static sf::Font font;
        font.loadFromFile(font_path);
        text.setFont(font);
        text.setCharacterSize(char_size);
    }
    void draw_property(sf::Color color, int index)
    {
        float offsetX = map_config.settings.offsetX;
        float offsetY = map_config.settings.offsetY;
        int margin = 100;
        sf::RectangleShape choise(sf::Vector2f(map_config.settings.windowX - offsetX, margin));
        sf::Text property_text;
        sf::Text property_value;

        install_font(property_text, 20, "../font/Ubuntu-Regular.ttf");
        install_font(property_value, 20, "../font/Ubuntu-Regular.ttf");
        choise.setPosition(sf::Vector2f(offsetX, offsetY + margin * index));
        choise.setFillColor(color);
        map_config.window_settings->draw(choise);

        property_text.setString(map_config.settings.property[index]);
        property_text.setPosition(sf::Vector2f(offsetX, offsetY + margin * index));
        map_config.window_settings->draw(property_text);
        property_value.setPosition(
                sf::Vector2f(map_config.settings.windowX - offsetX, offsetY + margin * index));
        property_value.setString(std::to_string(*map_config.settings.order[index]));
        map_config.window_settings->draw(property_value);
        map_config.window_settings->display();
    }
};