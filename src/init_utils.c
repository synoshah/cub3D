/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:45:27 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:45:27 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	reset_player_dir(t_player *player, char dir)
{
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->camera_x = 0.0;
	player->camera_y = 0.0;
	if (dir == 'N')
	{
		player->dir_y = -1.0;
		player->camera_x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir_y = 1.0;
		player->camera_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->camera_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->camera_y = -0.66;
	}
}

int	load_texture(void *mlx, t_data texture[], char *file_path)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(mlx, file_path, &width, &height);
	if (!texture->img)
	{
		printf("Error\nCould not load texture from %s\n", file_path);
		return (0);
	}
	texture->width = width;
	texture->height = height;
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	return (1);
}
