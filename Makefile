NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -Iinclude -Ilibft/include -Ilibft/src/get_next_line -Imlx

MLX_DIR = mlx
MLX_LIBS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
NRM_DIR = ./src ./include ./libft

SRCS = src/main.c \
	src/utils/error.c \
	src/parse/map_validating.c \
	src/parse/matrix.c \
	src/parse/parse_1.c \
	src/parse/parse_2.c \
	src/parse/parse_3.c \
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

RESET	= \033[0m
BOLD	= \033[1m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
RED		= \033[0;31m
CYAN	= \033[0;36m
GRAY	= \033[0;90m

TOTAL := $(words $(SRCS))
COUNT_FILE := .compile_count

all: $(NAME)

$(LIBFT_A):
	@printf "$(YELLOW)➜ Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null
	@printf "$(GREEN)✓ libft ready$(RESET)\n\n"

$(NAME): $(OBJS) $(LIBFT_A)
	@printf "$(YELLOW)➜ Building MiniLibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@printf "$(GREEN)✓ MiniLibX ready$(RESET)\n\n"
	@printf "$(YELLOW)➜ Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_LIBS) -o $(NAME)
	@rm -f $(COUNT_FILE)
	@printf "\n$(GREEN)$(BOLD)✓ cub3d compiled successfully!$(RESET)\n"
	@printf "$(GRAY)  run it with: ./cub3d <path/to/map.cub>$(RESET)\n\n"

%.o: %.c include/cub3d.h
	@n=$$(( $$(cat $(COUNT_FILE) 2>/dev/null || echo 0) + 1 )); \
	echo $$n > $(COUNT_FILE); \
	printf "$(CYAN)[%2d/%2d]$(RESET) Compiling %s\n" "$$n" "$(TOTAL)" "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(COUNT_FILE)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@printf "$(RED)✓ Object files removed$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@printf "$(RED)✓ $(NAME) binary removed$(RESET)\n"

re: fclean all

norm:
	@printf "$(CYAN)➜ Running norminette on necessary files...$(RESET)\n"
	@norminette $(NRM_DIR)

.PHONY: all clean fclean re norm