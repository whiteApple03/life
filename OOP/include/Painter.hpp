#pragma once

class Painter : public Storage {
protected:
    void print_figure(bool is_live, int coord_y, int coord_x)
    {
        float offsetX = map_config.offsetX;
        float offsetY = map_config.offsetY;
        sf::RectangleShape cell(sf::Vector2f(map_config.size_cell, map_config.size_cell));
        // cell.setScale(sf::Vector2f(0, 0));
        cell.setPosition(sf::Vector2f(
                coord_x * map_config.size_cell + offsetX,
                coord_y * map_config.size_cell + offsetY));
        cell.setFillColor((is_live) ? sf::Color::White : sf::Color::Black);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        map_config.window_p->draw(cell);
    }

    void print_manual()
    {
        int width = map_config.window_x;
        int startX = 0;
        float font_coof = 2;
        int y = map_config.window_y - map_config.offsetY / 2;
        std::vector<std::string> cur_manual_text;

        if (map_config.input_mode and !map_config.game_mode) {
            cur_manual_text = manual[0];
        } else {
            cur_manual_text = manual[1];
        }

        int mess_number = cur_manual_text.size();
        int unit = width / mess_number;
        int max_message_size = 0;

        for (int i = 0; i < mess_number; i++) {
            if (cur_manual_text[i].size() > max_message_size)
                max_message_size = cur_manual_text[i].size();
        }
        float font_size = (unit / static_cast<float>(max_message_size)) * font_coof;
        if (font_size > 20) {
            font_size = 20;
        }
        sf::Text manual_text;
        sf::Font font;
        font.loadFromFile("/home/saha/life/font/Ubuntu-Regular.ttf");
        manual_text.setFont(font);
        manual_text.setCharacterSize(font_size);
        map_config.window_p->draw(manual_text);
        map_config.window_p->display();
        for (int i = 0; i < mess_number; i++) {
            manual_text.setString(cur_manual_text[i]);
            manual_text.setPosition(sf::Vector2f(unit * i, y));
            map_config.window_p->draw(manual_text);
        }
    }

    void display()
    {
        for (int i = 0; i < map_config.field.sizeY; i++) {
            for (int k = 0; k < map_config.field.sizeX; k++) {
                print_figure(map_config.field.field[i][k], i, k);
            }
        }
        print_manual();
        map_config.window_p->display();
    }
    void display(std::vector<std::pair<int, int>> mas)
    {
        for (int i = 0; i < mas.size(); i++) {
            print_figure(
                    map_config.field.field[mas[i].first][mas[i].second],
                    mas[i].first,
                    mas[i].second);
        }
        map_config.window_p->display();
    }
    void clear()
    {
        for (int i = 0; i < map_config.field.sizeY; i++) {
            map_config.live_cell_sum[i] = 0;
            for (int k = 0; k < map_config.field.sizeX; k++) {
                map_config.field.field[i][k] = false;
            }
        }
        display();
    }
    void user_choise(int posX, int posY)
    {
        sf::RectangleShape cell(sf::Vector2f(map_config.size_cell, map_config.size_cell));
        cell.setPosition(sf::Vector2f(
                posX * map_config.size_cell + map_config.offsetX,
                posY * map_config.size_cell + map_config.offsetY));
        cell.setFillColor(sf::Color::Magenta);
        cell.setOutlineThickness(1);
        cell.setOutlineColor(sf::Color::White);
        map_config.window_p->draw(cell);
        map_config.window_p->display();
    }

private:
    static const int manual_size = 2;
    std::vector<std::vector<std::string>> manual
            = {{"Spase - input/game",
                "w, a, s, d - controlling",
                "enter - select cell",
                "LMB - change cell state",
                "k - clear map",
                "M - open settings"},
               {"Spase - input/game",
                "o - change generation",
                "r - auto/manual",
                "k = clear map",
                "M - open settings"}};
};