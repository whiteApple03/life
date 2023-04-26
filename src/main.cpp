#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>
#include <input.hpp>

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