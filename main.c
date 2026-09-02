#include "cub3D.h"
#include "include/map.h"
#include "include/parser.h"

int	handle_key_press(int keycode, t_context *ctx)
{
	if (keycode == KEY_ESC)
		close_game(ctx);
	if (keycode == KEY_W)
		ctx->keys->w = 1;
	if (keycode == KEY_S)
		ctx->keys->s = 1;	
	if (keycode == KEY_A)
		ctx->keys->a = 1;
	if (keycode == KEY_D)
		ctx->keys->d = 1;
	if (keycode == KEY_LEFT)
		ctx->keys->l = 1;
	if (keycode == KEY_RIGHT)
		ctx->keys->r = 1;
	if (keycode == KEY_X)
		ctx->keys->x = 1;
	return (0);
}

int	handle_key_release(int keycode, t_context *ctx)
{
	if (keycode == KEY_W)
		ctx->keys->w = 0;
	if (keycode == KEY_S)
		ctx->keys->s = 0;	
	if (keycode == KEY_A)
		ctx->keys->a = 0;
	if (keycode == KEY_D)
		ctx->keys->d = 0;
	if (keycode == KEY_LEFT)
		ctx->keys->l = 0;
	if (keycode == KEY_RIGHT)
		ctx->keys->r = 0;
	if (keycode == KEY_X)
		ctx->keys->x = 0;
	return (0);
}

void	free_textures(void *mlx, t_data textures[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (textures[i].img)
		{
			mlx_destroy_image(mlx, textures[i].img);
			textures[i].img = NULL;
		}
		i++;
	}
}

int close_game(t_context *ctx)
{
	printf("Game closed\n");
	free_textures(ctx->mlx, ctx->textures);
	free_map(ctx->map);
	if (ctx->title_img)
		mlx_destroy_image(ctx->mlx, ctx->title_img);
	if (ctx->end_img)
		mlx_destroy_image(ctx->mlx, ctx->end_img);
	mlx_destroy_image(ctx->mlx, ctx->img->img);
	mlx_destroy_window(ctx->mlx, ctx->mlx_win);
	if (ctx->mlx)
	{
		mlx_destroy_display(ctx->mlx);
		free(ctx->mlx);
	}
	exit(0);
}

int load_texture(void *mlx, t_data texture[], char *file_path)
{
	int width;
	int height;

	texture->img = mlx_xpm_file_to_image(mlx, file_path, &width, &height);
	if (!texture->img)
	{
		printf("could not load texture from %s\n", file_path);
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

int main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_player 	player = {0};
	t_data      img;
	t_map		*map;

	t_input			input = {0};
	t_context   	ctx = {0};
	t_game_state	game_state = {0};

	map = parse_map_file("maps/map1.cub");
	if (!map)
	{
		printf("failed to parse map.\n");
		return (1);
	}
	// spawn in the center of the grid
	player.pypos_x = map->spawn.x + 0.1;
	player.pypos_y = map->spawn.y + 0.1;

	// set vectors for spawn direction
	if (map->spawn.direction == 'N')
	{
		player.dir_x = 0.0;
		player.dir_y = -1.0;
		player.camera_x = 0.66;
		player.camera_y = 0.0;
	}
	else if (map->spawn.direction == 'S')
	{
		player.dir_x = 0.0;
		player.dir_y = 1.0;
		player.camera_x = -0.66;
		player.camera_y = 0.0;
	}
	else if (map->spawn.direction == 'E')
	{
		player.dir_x = 1.0;
		player.dir_y = 0.0;
		player.camera_x = 0.0;
		player.camera_y = 0.66;
	}
	else if (map->spawn.direction == 'W')
	{
		player.dir_x = -1.0;
		player.dir_y = 0.0;
		player.camera_x = 0.0;
		player.camera_y = -0.66;
	}
	player.dir_x = 0.0;
	player.dir_y = -1.0;
	player.camera_x = 0.66;
	player.camera_y = 0.0;
	player.move_speed = 0.1;
	player.rotation_speed = 0.05;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "cub3D");
	img.img = mlx_new_image(mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// draw_map(&img);
	// draw_player(&img, &player);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	ctx.player = &player;
	ctx.img = &img;
	ctx.mlx = mlx;
	ctx.mlx_win = mlx_win;
	ctx.keys = &input;
	ctx.map = map;
	ctx.game_state = &game_state;

	// paths saved in your parser.
	load_texture(mlx, &ctx.textures[0], ctx.map->textures.north);
	load_texture(mlx, &ctx.textures[1], ctx.map->textures.south);
	load_texture(mlx, &ctx.textures[2], ctx.map->textures.east);
	load_texture(mlx, &ctx.textures[3], ctx.map->textures.west);
	load_texture(mlx, &ctx.textures[4], "textures/cave_exit.xpm");
	ctx.textures[5].img = NULL;
	mlx_loop_hook(mlx, render_frame, &ctx);
	// Key press and key release events
	mlx_hook(mlx_win, 2, 1L<<0,  handle_key_press, &ctx);
	mlx_hook(mlx_win, 3, 1L<<1 ,handle_key_release, &ctx);
	mlx_do_key_autorepeatoff(mlx); // Idk what this does lol. 
	mlx_hook(mlx_win, 17, 0, close_game, &ctx);  
	mlx_loop(mlx);
	return 0;
}
