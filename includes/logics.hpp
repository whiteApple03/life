#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <Map.hpp>

#ifndef LOGICS_HPP
#define LOGICS_HPP
template<typename T1, typename T2>
int counting_live_cells(Map& map, T1 i, T2 k);

// int counting_live_cells(Map& map, int& i, int& k);
// int counting_live_cells(Map& map, int i, int k);

void change_state(Map& map);

void print_field(Map& map);

#endif