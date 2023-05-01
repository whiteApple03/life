#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>

#ifndef LOGICS_HPP
#define LOGICS_HPP

int counting_live_cells(Map& map, int& i, int& k);

void change_state(Map& map);

void print_field(Map& map);

#endif