/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:13:02 by synoshah          #+#    #+#             */
/*   Updated: 2026/08/12 16:13:02 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int player_angle(int angle)
{
    t_player player;
    int x;
    int y;
    if (angle == 'N')
    {
        player.dir_x = 0.0;
        player.dir_y = -1.0;
        player.camera_x = 0.66;
        player.camera_y = 0.0;
    }
    else if (angle == 'E')
    {
        player.dir_x = 1.0;
        player.dir_y = 0.0;
        player.camera_x = 0.0;
        player.camera_y = 0.66;
    }
    else if (angle == 'S')
    {
        player.dir_x = 0.0;
        player.dir_y = 1.0;
        player.camera_x = -0.66;
        player.camera_y = 0.0;
    }
    else if (angle == 'W')
    {
        player.dir_x = -1.0;
        player.dir_y = 0.0;
        player.camera_x = 0.0;
        player.camera_y = -0.66;
    }
}

int dir(int angle)
{
    int x;
    int y;
    int old_x = x;
    int old_y = y;

    angle = angle * (3.14/180);
    x = (old_x * cos(angle)) - (old_y * sin(angle));
    y = (old_x * sin(angle)) + (old_y * cos(angle));
}