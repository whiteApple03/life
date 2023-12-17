#pragma once 
#include "Adapter.hpp"
#include "Controlling.hpp"
#include "Helper.hpp"
#include "Painter.hpp"
#include "Painter_settings.hpp"

class Settings_window_controlling : Controlling, public Painter_settings, Helper, Painter, Adapter {
public:
    Settings_window_controlling()
    {
    }

    void input_keyboard(sf::Event& event)
    {
        std::string new_value;
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::M:
                relocate();

                map_config.window_settings->close();
                map_config.window_p->display();
                return;
            case sf::Keyboard::Up:
                draw_property(sf::Color::Black, map_config.settings.cur_choise);

                map_config.settings.cur_choise
                        = ((map_config.settings.cur_choise - 1 < 0)
                                   ? map_config.settings.property.size() - 2
                                   : (map_config.settings.cur_choise - 1)
                                           % (map_config.settings.property.size() - 1));
                draw_property(sf::Color::Blue, map_config.settings.cur_choise);
                break;
            case sf::Keyboard::Down:
                draw_property(sf::Color::Black, map_config.settings.cur_choise);

                map_config.settings.cur_choise = (map_config.settings.cur_choise + 1)
                        % (map_config.settings.property.size() - 1);
                draw_property(sf::Color::Blue, map_config.settings.cur_choise);

                break;
            case sf::Keyboard::Enter:
                draw_property(sf::Color::Red, map_config.settings.cur_choise);

                while (map_config.window_settings->waitEvent(event)) {
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (*map_config.settings.order[map_config.settings.cur_choise] == 0) {
                                continue;
                            }
                            map_config.settings.is_changed = true;
                            break;
                        }
                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (new_value.size() > 1) {
                                new_value.pop_back();
                                *map_config.settings.order[map_config.settings.cur_choise]
                                        = std::stoi((new_value.c_str()));
                                draw_property(sf::Color::Red, map_config.settings.cur_choise);

                                continue;
                            } else {
                                if (new_value.size() != 0)
                                    new_value.pop_back();
                                *map_config.settings.order[map_config.settings.cur_choise] = 0;
                                draw_property(sf::Color::Red, map_config.settings.cur_choise);
                            }
                        }
                    }
                    if (event.type == sf::Event::TextEntered) {
                        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                            if (new_value.size() < 5 and event.text.unicode >= '0'
                                and event.text.unicode <= '9') {
                                new_value.push_back(event.text.unicode);
                                *map_config.settings.order[map_config.settings.cur_choise]
                                        = std::stoi((new_value.c_str()));
                                draw_property(sf::Color::Red, map_config.settings.cur_choise);
                            }
                        }
                    }
                }
                switch (map_config.settings.cur_choise) {
                case 0:
                    map_config.field.sizeX = std::stoi((new_value.c_str()));
                    break;
                case 1:
                    map_config.field.sizeY = std::stoi((new_value.c_str()));
                    break;
                case 2:
                    map_config.delay_between_changed_generations = std::stoi((new_value.c_str()));
                    break;
                default:
                    break;
                }
                *map_config.settings.order[map_config.settings.cur_choise]
                        = std::stoi((new_value.c_str()));
                draw_settings();

                break;

            default:
                break;
            }
        }
    }

private:
    void relocate()
    {
        map_config.input_mode = true;
        map_config.settings_mode = false;
        calculate_cell_size();
        calc_offsets();
        if (map_config.settings.is_changed)
            allocate_memory_for_field(map_config.field);
        map_config.window_p->clear();
        display();
    }
};