/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:38:53 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:38:53 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "shapes.h"
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_colors
{
	int	floor;
	int	ceiling;
}	t_colors;

typedef struct s_map_size
{
	size_t	height;
	size_t	width;
}	t_map_size;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_spawn
{
	size_t	x;
	size_t	y;
	char	direction;
}	t_spawn;

typedef struct s_map
{
	t_map_size	size;
	t_colors	colors;
	t_textures	textures;
	t_spawn		spawn;
	char		**grid;
}	t_map;

typedef struct s_flags
{
	int	found_textures[4];
	int	in_map;
	int	found_floor;
	int	found_ceiling;
	int	height;
	int	width;
}	t_flags;

void	draw_background(t_data *img, int ceiling_color, int floor_color);
int		add_color(t_colors *colors, char *line, t_flags *flags);
char	*get_tex(t_map *map, char *line);
void	free_map(t_map *map);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_blank_line(char *line);
int		is_spawn_point(char c);
int		all_textures_found(int *found_textures);
int		add_texture(t_textures *tex, t_flags *flags, char *line);

#endif
