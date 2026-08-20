NAME        = cub3D

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

MLX_DIR     = ./minilibx-linux
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
INCLUDES    = -I. -I$(MLX_DIR) -I./libft -I./include

SRCS        = 	my_pixel_put.c  shapes.c  draw_line.c  map_utils/map.c  parser/free_map.c\
				parser/get_texture_path.c  parser/parse_cub_file.c\
				parser/get_map_dimension.c  parser/parse_color.c \
				parser/parse_helper.c\
				render_frame.c \
				parser/parse_main.c flood_fill.c
# main.c 
OBJS        = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft

%.o: %.c cub3D.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
# make clean -C ./libft 

fclean: clean
	rm -f $(NAME)
# make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re