#include <iostream>
#include <map>
#include <string>
#include <vector>


#include <Map.hpp>

void allocate_memory_for_field(Map& map)
{
    map.field = new bool*[map.sizeY];
    for (int i = 0; i < map.sizeY; i++)
        map.field[i] = new bool[map.sizeX];
}

int get_int(std::string& input, int& i)
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

void get_map_from_user(Map& map)
{
    map.sizeX = 9;
    map.sizeY = 9;
    allocate_memory_for_field(map);
    std::cout << "Введите живую клетку в формате: X,Y\nЧтобы закончить ввод "
                 "введите '-1'\n";
    std::string input;

    while (true) {
        std::pair<int, int> coords;
        getline(std::cin, input);
        int i = 0;
        coords.first = get_int(input, i) - 1;
        if (coords.first == -2)
            break;
        coords.second = get_int(input, i) - 1;
        map.field[coords.second][coords.first]
                = !map.field[coords.second][coords.first];
    }
}
int counting_live_cells(Map& map, int& i, int& k)
{
    int count = 0;
    if (i > 0) {
        count += map.field[i - 1][k];
    }
    if (k > 0) {
        count += map.field[i][k - 1];
    }
    if (i < map.sizeX - 1) {
        count += map.field[i + 1][k];
    }
    if (k < map.sizeY - 1) {
        count += map.field[i][k + 1];
    }
    if (i > 0 and k > 0) {
        count += map.field[i - 1][k - 1];
    }
    if (i < map.sizeX - 1 and k > 0) {
        count += map.field[i + 1][k - 1];
    }
    if (i < map.sizeX - 1 and k < map.sizeY - 1) {
        count += map.field[i + 1][k + 1];
    }
    if (i > 0 and k < map.sizeY - 1) {
        count += map.field[i - 1][k + 1];
    }
    return count;
}

void change_state(Map& map)
{
    std::vector<std::pair<int, int>> changed_cage;
    for (int i = 0; i < map.sizeX; i++) {
        for (int k = 0; k < map.sizeY; k++) {
            std::pair<int, int> cur_coord;
            if (map.field[i][k]
                and !(counting_live_cells(map, i, k) == 2
                      or counting_live_cells(map, i, k) == 3)) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);

            } else if (
                    !map.field[i][k] and counting_live_cells(map, i, k) == 3) {
                cur_coord.first = i;
                cur_coord.second = k;
                changed_cage.push_back(cur_coord);
            }
        }
    }

    for (int i = 0; i < changed_cage.size(); i++) {
        map.field[changed_cage[i].first][changed_cage[i].second]
                = !map.field[changed_cage[i].first][changed_cage[i].second];
    }
}

void print_field(Map& map)
{
    for (int i = 0; i < map.sizeY; i++) {
        std::cout << "|\t";
        for (int k = 0; k < map.sizeX; k++) {
            std::cout << map.field[i][k] << "\t";
        }
        std::cout << "|\n";
    }
}

void game_procces(Map& map)
{
    char answer;
    print_field(map);

    do {
        std::cout << "next step?(y/n): ";
        std::cin >> answer;
        change_state(map);
        print_field(map);
        std::cout << '\n' << answer;

    } while (answer == 'y');
}

int main()
{
    Map my_map;
    get_map_from_user(my_map);
    game_procces(my_map);
    return 0;
}