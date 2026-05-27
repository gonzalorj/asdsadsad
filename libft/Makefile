# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gorodrig <gorodrig@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 14:04:29 by gorodrig          #+#    #+#              #
#    Updated: 2024/04/02 15:44:39 by gorodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
RM = rm -f
CC = gcc
CFLAGS = -Wall -Werror -Wextra

SOURCE_FILES =	ft_bzero.c \
				ft_atoi.c  \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_error.c \
				ft_itoa.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putnbr_fd.c \
				ft_putendl_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strcmp.c \
				ft_atoll.c \
				ft_free_array.c \
				ft_square.c \
				ft_isspace.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_free_split.c \
				ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \
				

BONUS_SOURCE_FILES = ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \



OBJECTS = $(SOURCE_FILES:.c=.o)

BONUS_OBJECTS = $(BONUS_SOURCE_FILES:.c=.o)

$(NAME) : $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

all: $(NAME) 

bonus : $(OBJECTS) $(BONUS_OBJECTS)
	@ar rcs $(NAME) $(BONUS_OBJECTS)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all bonus

.PHONY:  all clean fclean re
