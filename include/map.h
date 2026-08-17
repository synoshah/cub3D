
#ifndef MAP_H
#define MAP_H

#include "shapes.h"
#include <stdlib.h>
#include "../cub3D.h"

typedef struct s_map
{
	size_t	height;
	size_t	width;
	int		floor_color;
	int		celing_color;
	char	*path_n;
	char	*path_s;
	char	*path_w;
	char	*path_e;
	char	**map;
}	t_map;

// TODO: These Need to take a map as a parameter
void	draw_map(t_data *img);
void	draw_player(t_data *img, t_player *player);
void	clear_display(t_data *img);

// parser
t_map	*parse_cub_file(char *filename);
int		get_color(t_map *map, char *line);
char	*get_tex(t_map *map, char *line);
void	free_map(t_map *map);

#endif