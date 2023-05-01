#include <iostream>
#include <string>

#include <Map.hpp>

#ifndef INPUT_HPP
#define INPUT_HPP

void allocate_memory_for_field(Map&);

int get_int(std::string&, int&);

void get_map_from_user(Map&);

#endif