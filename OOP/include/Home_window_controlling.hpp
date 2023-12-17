#include "chrono"


#include "Controlling.hpp"
#include "Helper.hpp"
#include "Logic.hpp"
#include "Painter.hpp"
#include "Settings_renderer.hpp"


class Home_window_controlling : public Controlling, public Painter, public Helper, public Logic {
public:
    Home_window_controlling()
    {
    }

    void menu_controlling(sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Space:
                if (map_config.auto_change == true)
                    break;
                if (map_config.input_mode) {
                    setGameMode();
                } else {
                    setInputMode();
                }
                map_config.window_p->clear();
                display();
                return;
                break;
            case sf::Keyboard::K:
                clear();
                break;
            case sf::Keyboard::R:
                map_config.cur_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                                              std::chrono::system_clock::now().time_since_epoch())
                                              .count();
                map_config.auto_change = !map_config.auto_change;
                break;
            case sf::Keyboard::M:
                setSettingMode();

                break;
            default:
                break;
            }
        }
    }

    void auto_change()
    {
        if (map_config.game_mode and !map_config.input_mode and !map_config.settings_mode) {
            auto time_now = std::chrono::system_clock::now();
            int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                 time_now.time_since_epoch())
                                 .count();

            if (map_config.auto_change) {
                if (map_config.cur_time + map_config.delay_between_changed_generations < ms) {
                    display(change_state(map_config.field));
                    map_config.cur_time = ms;
                }
            }
        }
    }

    void Map_controlling(sf::Event& event)
    {
        if (map_config.game_mode and !map_config.input_mode and !map_config.settings_mode) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::O) {
                    display(change_state(map_config.field));
                }
            }
        }

        else if (
                !map_config.game_mode and map_config.input_mode and !map_config.settings_mode
                and !map_config.is_resized) {
            if (event.type == sf::Event::KeyPressed) {
                input_keyboard(event);
            }
            if (!map_config.is_resized and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                process_mouse_click();
            }
        } else if (map_config.settings_mode and !map_config.game_mode and !map_config.input_mode) {
            Settings_renderer setting_renderer;
            setting_renderer.loop();
            // delete &setting_renderer;
        }
    }

    void process_mouse_click()
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(*map_config.window_p);
        int cellX = (mouse_pos.x - map_config.offsetX) / map_config.size_cell;
        int cellY = (mouse_pos.y - map_config.offsetY) / map_config.size_cell;
        if (cellX == last_clickX and cellY == last_clickY) {
            return;
        }
        if (cellX >= map_config.field.sizeX or cellY >= map_config.field.sizeY or cellX < 0
            or cellY < 0) {
            return;
        }

        last_clickX = cellX;
        last_clickY = cellY;
        map_config.field.field[cellY][cellX] = !map_config.field.field[cellY][cellX];
        if (map_config.field.field[cellY][cellX]) {
            map_config.live_cell_sum[cellY]++;
        } else {
            map_config.live_cell_sum[cellY]--;
        }
        print_figure(map_config.field.field[cellY][cellX], cellY, cellX);
        map_config.window_p->display();
    }
    void input_keyboard(sf::Event& event)
    {
        std::pair<int, int> change_cage;
        switch (event.key.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            print_figure(map_config.field.field[posY][posX], posY, posX);
            posY = (map_config.field.sizeY + ((posY - 1) % map_config.field.sizeY))
                    % map_config.field.sizeY;
            user_choise(posX, posY);

            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:

            print_figure(map_config.field.field[posY][posX], posY, posX);

            posX = (map_config.field.sizeX + ((posX - 1) % map_config.field.sizeX))
                    % map_config.field.sizeX;
            user_choise(posX, posY);
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            print_figure(map_config.field.field[posY][posX], posY, posX);
            posY = (map_config.field.sizeY + ((posY + 1) % map_config.field.sizeY))
                    % map_config.field.sizeY;
            user_choise(posX, posY);
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            print_figure(map_config.field.field[posY][posX], posY, posX);
            posX = (map_config.field.sizeX + ((posX + 1) % map_config.field.sizeX))
                    % map_config.field.sizeX;
            user_choise(posX, posY);
            break;
        case sf::Keyboard::Enter:
            map_config.field.field[posY][posX] = !map_config.field.field[posY][posX];
            if (map_config.field.field[posY][posX]) {
                map_config.live_cell_sum[posY]++;
            } else {
                map_config.live_cell_sum[posY]--;
            }
            break;
        default:
            break;
        }
        return;
    }

private:
    int last_clickX = -1;
    int last_clickY = -1;
    int posX = 0;
    int posY = 0;
};
