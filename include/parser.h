/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 21:46:45 by synoshah          #+#    #+#             */
/*   Updated: 2026/09/03 21:46:45 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../include/map.h"
# include <fcntl.h>
# include "../libft/libft.h"

int		parse_map_metadata(t_map *map, int fd);
int		add_color(t_colors *colors, char *line, t_flags *flags);
int		add_texture(t_textures *tex, t_flags *flags, char *line);
void	free_map(t_map *map);
int		load_map_grid(t_map *map, int fd);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		is_blank_line(char *line);
int		is_spawn_point(char c);
int		all_textures_found(int *found_textures);
int		flood(t_map *map, int x, int y);
t_map	*parse_map_file(char *filename);

#endif
