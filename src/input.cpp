#include <chrono>
#include <map>
#include <string>
#include <vector>

#include <Game.hpp>

int Game::Input::get_int(std::string& input, int& i)
{
    std::string digit;
    for (; i < input.size() && input[i] != ','; i++) {
        if (input[i] == ' ')
            continue;
        digit.push_back(input[i]);
    }
    i++;
    return stod(digit);
}

void Game::Input::print_squard(bool is_live, int coordY, int coordX)
{
    float offsetX = config->offsetX;
    float offsetY = config->offsetY;
    sf::RectangleShape cell(sf::Vector2f(config->size_cell, config->size_cell));
    // cell.setScale(sf::Vector2f(0, 0));
    cell.setPosition(sf::Vector2f(
            coordX * config->size_cell + offsetX, coordY * config->size_cell + offsetY));
    cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);
    config->window_p->draw(cell);
}

void Game::Input::allocate_memory_for_field(Game::Field_t& map)
{
    map.field = new bool*[map.sizeY];
    for (int i = 0; i < map.sizeY; i++) {
        map.field[i] = new bool[map.sizeX];
        for (int k = 0; k < map.sizeX; k++) {
            map.field[i][k] = 0;
        }
    }
}

void Game::Game_window::setInputMode()
{
    config->input_mode = true;
    config->game_mode = false;
    config->settings_mode = false;
}

void Game::Input::process_mouse_click()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*config->window_p);
    int cellX = (mouse_pos.x - config->offsetX) / config->size_cell;
    int cellY = (mouse_pos.y - config->offsetY) / config->size_cell;
    if (cellX == last_clickX and cellY == last_clickY) {
        return;
    }
    if (cellX >= config->field.sizeX or cellY >= config->field.sizeY or cellX < 0 or cellY < 0) {
        return;
    }

    last_clickX = cellX;
    last_clickY = cellY;
    config->field.field[cellY][cellX] = !config->field.field[cellY][cellX];
    if (config->field.field[cellY][cellX]) {
        config->live_cell_sum[cellY]++;
    } else {
        config->live_cell_sum[cellY]--;
    }
    print_squard(config->field.field[cellY][cellX], cellY, cellX);
}

void Game::Input::user_choise()
{
    sf::RectangleShape cell(sf::Vector2f(config->size_cell, config->size_cell));
    cell.setPosition(sf::Vector2f(
            posX * config->size_cell + config->offsetX,
            posY * config->size_cell + config->offsetY));
    cell.setFillColor(sf::Color::Magenta);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::White);
    config->window_p->draw(cell);
}

void Game::Input::clear()
{
    for (int i = 0; i < config->field.sizeY; i++) {
        config->live_cell_sum[i] = 0;
        for (int k = 0; k < config->field.sizeX; k++) {
            config->field.field[i][k] = false;
        }
    }
    display();
}

void Game::Input::input_keyboard(sf::Event& event)
{
    std::pair<int, int> change_cage;
    switch (event.key.code) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        print_squard(config->field.field[posY][posX], posY, posX);
        posY = (config->field.sizeY + ((posY - 1) % config->field.sizeY)) % config->field.sizeY;
        user_choise();

        break;
    case sf::Keyboard::A:
    case sf::Keyboard::Left:

        print_squard(config->field.field[posY][posX], posY, posX);

        posX = (config->field.sizeX + ((posX - 1) % config->field.sizeX)) % config->field.sizeX;
        user_choise();
        break;
    case sf::Keyboard::S:
    case sf::Keyboard::Down:
        print_squard(config->field.field[posY][posX], posY, posX);
        posY = (config->field.sizeY + ((posY + 1) % config->field.sizeY)) % config->field.sizeY;
        user_choise();
        break;
    case sf::Keyboard::D:
    case sf::Keyboard::Right:
        print_squard(config->field.field[posY][posX], posY, posX);
        posX = (config->field.sizeX + ((posX + 1) % config->field.sizeX)) % config->field.sizeX;
        user_choise();
        break;
    case sf::Keyboard::Enter:
        config->field.field[posY][posX] = !config->field.field[posY][posX];
        if (config->field.field[posY][posX]) {
            config->live_cell_sum[posY]++;
        } else {
            config->live_cell_sum[posY]--;
        }
        break;
    default:
        break;
    }
    return;
}

void Game::Game_window::setSettingMode()
{
    config->settings_mode = true;
    config->game_mode = false;
    config->input_mode = false;
}

void Game::Game_window::game(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Space:
            if (config->auto_change == true)
                break;
            if (config->input_mode) {
                setGameMode();
            } else {
                setInputMode();
            }
            config->window_p->clear();
            display();
            return;
            break;
        case sf::Keyboard::K:
            input_p->clear();
            break;
        case sf::Keyboard::R:
            config->cur_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                                       std::chrono::system_clock::now().time_since_epoch())
                                       .count();
            config->auto_change = !config->auto_change;
            break;
        case sf::Keyboard::M:
            setSettingMode();
            break;
        default:
            break;
        }
    }
    if (config->game_mode and !config->input_mode and !config->settings_mode) {
        auto time_now = std::chrono::system_clock::now();
        int64_t ms
                = std::chrono::duration_cast<std::chrono::milliseconds>(time_now.time_since_epoch())
                          .count();

        if (config->auto_change) {
            if (config->cur_time + config->delay_between_changed_generations < ms) {
                input_p->display(logic_p->change_state(config->field));
                config->cur_time = ms;
            }
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::O) {
                input_p->display(logic_p->change_state(config->field));
            }
        }
    } else if (!config->game_mode and config->input_mode and !config->settings_mode) {
        if (event.type == sf::Event::KeyPressed) {
            input_p->input_keyboard(event);
            // if (input_p->input_keyboard(event)) {
            //     setGameMode();
            // };
        }
        if (!config->is_resized and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            input_p->process_mouse_click();
        }
    } else if (config->settings_mode and !config->game_mode and !config->input_mode) {
    }
    resized(event);
}

void Game::Game_window::resized(sf::Event& event)
{
    static int width, height;
    if (event.type == sf::Event::Resized) {
        config->is_resized = true;
        height = event.size.height;
        width = event.size.width;
        config->window_p->clear();
        config->window_p->display();
    } else if (config->is_resized) {
        config->is_resized = false;
        input_p->resized(width, height);
        display();
    }
}