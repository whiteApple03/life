#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>
#include <input.hpp>
#include <logics.hpp>


int main()
{
    Map my_map;
    get_map_from_user(my_map);
    game_procces(my_map);
    return 0;
}