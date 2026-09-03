/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:01:57 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:01:57 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_texture_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return ((!ft_strncmp(line + i, "NO", 2)
			|| !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "WE", 2)
			|| !ft_strncmp(line + i, "EA", 2))
		&& (line[i + 2] == ' ' || line[i + 2] == '\t'));
}

int	is_color_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return ((line[i] == 'F' || line[i] == 'C')
		&& (line[i + 1] == ' ' || line[i + 1] == '\t'));
}

int	is_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\r' || line[i] == '\n'))
		i++;
	return (line[i] == '\0');
}

int	is_spawn_point(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	all_textures_found(int *found_textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!found_textures[i])
			return (0);
		i++;
	}
	return (1);
}
