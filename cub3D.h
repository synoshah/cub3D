#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <mlx.h>
# include <math.h>

# include "include/image.h"
# include "include/shapes.h"
# include "include/game_state.h"
# include "include/map.h"
# include "include/draw.h"
# include "include/parser.h"

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define TILE_SIZE 16

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
	int		tex_index;
	int		color;
}	t_ray;

typedef struct s_player
{
	double	pypos_x;
	double	pypos_y;
	double	dir_x;
	double	dir_y;
	double	camera_x;
	double	camera_y;
	double	move_speed;
	double	rotation_speed;
	void	*player;
}	t_player;

typedef struct s_input
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	l;
	int	r;
}	t_input;

typedef struct s_context
{
	t_player		*player;
	t_data			*img;
	void			*mlx;
	void			*mlx_win;
	t_input			*keys;
	struct s_map	*map;
	t_data			textures[5];
	t_game_state	*game_state;
}	t_context;

int		render_frame(t_context *ctx);
int		handle_key(t_context *ctx);
void	load_texture(void *mlx, t_data texture[], char *file_path);
void	init_ray(t_context *ctx, t_ray *ray, int x);
void	perform_dda(t_context *ctx, t_ray *ray);
void	calc_wall_height(t_ray *ray);
void	get_texture_index(t_context *ctx, t_ray *ray);
void	calc_texture_x(t_context *ctx, t_ray *ray);
void	draw_wall_slice(t_context *ctx, t_ray *ray, int x);
void	render_start(t_context *ctx);
void	render_playing(t_context *ctx);
void	load_next_level(t_context *ctx);
void	render_end_screen(t_context *ctx);
void	draw_start_text(t_context *ctx);

#endif