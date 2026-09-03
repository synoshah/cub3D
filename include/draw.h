/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:40:24 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:40:25 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "image.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

void	draw_line(t_data *img, t_point start, t_point end, int color);
void	my_pixel_put(t_data *img, int x, int y, int color);
int		get_texture_pixel(t_data *texture, int x, int y);

#endif
