/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:04:52 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:04:52 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static int	is_valid_map_cell(char c)
{
	return (c == '1'
		|| c == '0'
		|| c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W'
		|| c == ' '
		|| c == 'X');
}

static int	store_map_row(t_map *map, char *line, int *found, int y)
{
	int	x;
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	x = -1;
	while (line[++x])
	{
		if (!is_valid_map_cell(line[x]) && !is_spawn_point(line[x]))
			return (0);
		if (is_spawn_point(line[x]) && *found)
			return (0);
		if (is_spawn_point(line[x]))
		{
			map->spawn.x = x;
			map->spawn.y = y;
			map->spawn.direction = line[x];
			*found = 1;
		}
	}
	map->grid[y] = ft_strdup(line);
	return (map->grid[y] != NULL);
}

static void	advance_to_map_content(char **line, int fd)
{
	while (*line)
	{
		if (!is_blank_line(*line)
			&& !is_color_line(*line)
			&& !is_texture_line(*line))
		{
			return ;
		}
		free(*line);
		*(line) = get_next_line(fd);
	}
}

static void	flush_gnl(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	load_map_grid(t_map *map, int fd)
{
	char	*line;
	int		y;
	int		found_spawn;

	map->grid = ft_calloc(map->size.height, sizeof(char *));
	if (!map->grid)
		return (0);
	y = 0;
	found_spawn = 0;
	line = get_next_line(fd);
	advance_to_map_content(&line, fd);
	while (line)
	{
		if (!store_map_row(map, line, &found_spawn, y))
		{
			flush_gnl(line, fd);
			return (0);
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	return (found_spawn);
}
