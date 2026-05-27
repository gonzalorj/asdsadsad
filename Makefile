NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude -Ilibft/include -Ilibft/src/get_next_line

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = src/main.c \
	src/init/init.c \
	src/free_error.c/error.c \
	src/parse/parse_1.c \
	src/parse/parse_2.c \
	src/parse/parse_cub_file.c \
	src/parse/parse_utils.c \
	src/parse/parser_colors.c \
	src/parse/parser_texture.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -o $(NAME)

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
