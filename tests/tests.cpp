#include <ctest.h>

#include <Map.hpp>
#include <input.hpp>
#include <logics.hpp>

CTEST(logic, createmap)
{
    bool map[9][9]
            = {{0, 1, 0, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {1, 0, 1, 0, 0, 0, 0, 0, 0},
               {0, 1, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0},
               {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    Map field = {9, 9};
		allocate_memory_for_field(field);
		field.field = (bool**)map;
		
}