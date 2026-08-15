#include "cub3D.h"

void flood(char **map, int x, int y, int limit)
{
    if (x <  0 || y < 0 || map[x][y] > limit)
    {
        write(1, "Unclosed walls\n", 15);
        return ;
    }
    else if (px >= limit || py >= limit)
    {
        write(1, "Player initialized outside of walls\n", 35);
        return ;
    }
    map[x][y] = 'V';
    if (map[x][y] || == 'V' map[x][y] == '1')
        return ;
    flood(map, x + 1, y, limit);
    flood(map, x - 1, y, limit);
    flood(map, x, y + 1, limit);
    flood(map, x, y - 1, limit);
}

