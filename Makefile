NAME        = cub3D
BONUS_NAME  = cub3D_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_DIR     = ./minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES    = -I. -I$(MLX_DIR) -I./libft -I./include
LIBFT       = ./libft/libft.a

SRCS        = src/my_pixel_put.c \
              src/shapes.c \
              src/draw_line.c \
              src/flood_fill.c \
              src/init_utils.c \
              src/main.c \
              src/map_utils/map.c \
              src/parser/fill_map.c \
              src/parser/free_map.c \
              src/parser/get_texture_path.c \
              src/parser/parse_color.c \
              src/parser/parse_header.c \
              src/parser/parse_map_file.c \
              src/parser/parse_helper.c \
              src/render_engine/raycaster.c \
              src/render_engine/render_wall.c \
              src/render_engine/key_hooks.c \
              src/render_engine/render_frame.c \
              src/render_engine/handle_key.c

B_SRCS      = src_bonus/my_pixel_put_bonus.c \
              src_bonus/shapes_bonus.c \
              src_bonus/draw_line_bonus.c \
              src_bonus/flood_fill_bonus.c \
              src_bonus/init_utils_bonus.c \
              src_bonus/main_bonus.c \
              src_bonus/level_manager_bonus.c \
              src_bonus/map_utils/map_bonus.c \
              src_bonus/parser/fill_map_bonus.c \
              src_bonus/parser/free_map_bonus.c \
              src_bonus/parser/get_texture_path_bonus.c \
              src_bonus/parser/parse_color_bonus.c \
              src_bonus/parser/parse_header_bonus.c \
              src_bonus/parser/parse_map_file_bonus.c \
              src_bonus/parser/parse_helper_bonus.c \
              src_bonus/render_engine/raycaster_bonus.c \
              src_bonus/render_engine/render_wall_bonus.c \
              src_bonus/render_engine/key_hooks_bonus.c \
              src_bonus/render_engine/render_frame_bonus.c \
              src_bonus/render_engine/handle_key_bonus.c \
              src_bonus/render_engine/render_story_bonus.c \
              src_bonus/reload_textures_bonus.c \

OBJS        = $(SRCS:.c=.o)
B_OBJS      = $(B_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) $(MLX_FLAGS) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(B_OBJS)
	make clean -C ./libft

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re bonus