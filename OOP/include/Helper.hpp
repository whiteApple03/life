#pragma once

#include "../configurate/map_config.hpp"

class Helper : public Storage {
protected:
    void allocate_memory_for_field(Field_t& map)
    {
        map.field = new bool*[map.sizeY];
        map_config.live_cell_sum = new int[map.sizeY];
        for (int i = 0; i < map.sizeY; i++) {
            map.field[i] = new bool[map.sizeX];
            map_config.live_cell_sum[i] = 0;
            for (int k = 0; k < map.sizeX; k++) {
                map.field[i][k] = 0;
            }
        }
    }
    void setInputMode()
    {
        map_config.input_mode = true;
        map_config.game_mode = false;
        map_config.settings_mode = false;
    }
    void setGameMode()
    {
        map_config.game_mode = true;
        map_config.input_mode = false;
        map_config.settings_mode = false;
    }

    void setSettingMode()
    {
        map_config.game_mode = false;
        map_config.input_mode = false;
        map_config.settings_mode = true;
    }
};