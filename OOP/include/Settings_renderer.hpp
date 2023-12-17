#pragma once
#include "Settings_window_controlling.hpp"

class Settings_renderer : public Settings_window_controlling {
public:
    Settings_renderer()
    {
        configurate_settings();
    }

    ~Settings_renderer() {
        delete map_config.window_settings;
    }

    void loop()
    {
        while (map_config.window_settings->isOpen()) {
            static sf::Event settings_event;
            if (map_config.window_settings->pollEvent(settings_event)) {
                if (settings_event.type == sf::Event::Resized) {
                    sf::FloatRect visiableArea(
                            0, 0, map_config.settings.windowX, map_config.settings.windowY);
                    map_config.window_settings->setView(sf::View(visiableArea));
                    draw_settings();
                }
                if (settings_event.type == sf::Event::Closed){
                    map_config.window_settings->close();
                    setInputMode();
                }
                input_keyboard(settings_event);
            }
        }
    }

private:
    void configurate_settings()
    {
        map_config.settings.x = map_config.field.sizeX;
        map_config.settings.y = map_config.field.sizeY;
        map_config.settings.windowX = map_config.window_x;
        map_config.settings.windowY = map_config.window_y;
        map_config.settings.offsetX = map_config.settings.windowX * map_config.margin;
        map_config.settings.offsetY = map_config.settings.windowY * map_config.margin;
        map_config.window_settings = new sf::RenderWindow(
                sf::VideoMode(map_config.settings.windowX, map_config.settings.windowY),
                "settings");
        map_config.window_settings->setPosition(sf::Vector2i(0, 0));
        map_config.window_settings->setKeyRepeatEnabled(false);

        draw_settings();
    }
};