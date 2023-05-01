#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>
#include <input.hpp>
#include <logics.hpp>

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