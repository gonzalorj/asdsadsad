NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -Iinclude -Ilibft/include -Ilibft/src/get_next_line -Imlx

MLX_DIR = mlx
MLX_LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/utils/error.c \
	src/parse/map_validating.c \
	src/parse/matrix.c \
	src/parse/parse_1.c \
	src/parse/parse_2.c \
	src/parse/parse_3.c \
	src/parse/parse_cub_file.c \
	src/parse/parse_utils.c \
	src/parse/parser_colors.c \
	src/parse/parser_texture.c \
	src/utils/hooks.c \
	src/renders/position.c \
	src/renders/raycast.c \
	src/renders/render.c \
	src/renders/textures.c \
	src/utils/utils.c \
	src/utils/utils2.c \
	src/renders/walk.c \
	src/renders/walls.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_LIBS) -o $(NAME)

%.o: %.c include/cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
