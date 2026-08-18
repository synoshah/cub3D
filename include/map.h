
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
	char	**map;
	char	*path_n;
	char	*path_s;
	char	*path_w;
	char	*path_e;
}	t_map;

// TODO: These 3 Need to take a map as a parameter
void	draw_map(t_data *img);
void	draw_player(t_data *img, t_player *player);
void	clear_display(t_data *img);

// parser
t_map	*parse_cub_file(char *filename);
int		get_color(char *line);
char	*get_tex(t_map *map, char *line);
void	free_map(t_map *map);

int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_blank_line(char *line);
int		all_textures_found(int *found_textures);
int		add_texture(int *found_textures, char *line);

#endif