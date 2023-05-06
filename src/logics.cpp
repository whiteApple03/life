#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>

template<typename T1, typename T2>

int counting_live_cells(Map& map, T1 i, T2 k)
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