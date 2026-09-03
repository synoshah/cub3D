/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:46:59 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:47:00 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "image.h"
# include "draw.h"

void	draw_circle(t_data *img, t_point point, int color, int radius);
void	draw_square(t_data *img, t_point point, int color, int size);

#endif