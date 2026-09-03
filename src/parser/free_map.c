/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbaras <fbaras@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:08:26 by fbaras            #+#    #+#             */
/*   Updated: 2026/09/03 21:08:26 by fbaras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->textures.east)
			free(map->textures.east);
		if (map->textures.north)
			free(map->textures.north);
		if (map->textures.south)
			free(map->textures.south);
		if (map->textures.west)
			free(map->textures.west);
		if (map->grid != NULL)
		{
			i = 0;
			while (i < (int)map->size.height && map->grid[i])
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
	map = NULL;
}
