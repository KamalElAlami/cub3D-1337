# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 03:44:02 by kael-ala          #+#    #+#              #
#    Updated: 2024/10/23 14:53:06 by kael-ala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

# MLX42
MLX42_PATH = ./MLX42
MLX42_BUILD = $(MLX42_PATH)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a

# LIBFT
LIBFT_PATH = ./lib
LIBFT = $(LIBFT_PATH)/libft.a

# Includes
INCLUDES = -I./includes -I$(MLX42_PATH)/include -I$(LIBFT_PATH)

# Sources
SRCS = src/main.c src/parse.c src/parse_utilities.c src/graphics.c src/utilities.c src/raycasting.c src/raycasting_utils.c

# Objects
OBJS = $(SRCS:.c=.o)

# Libraries
LIBS = $(MLX42_LIB) $(LIBFT) -lglfw -L"/Users/kael-ala/.brew/Cellar/glfw/3.4/lib/"

all: $(NAME)

$(NAME): $(MLX42_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX42_LIB):
	cmake $(MLX42_PATH) -B $(MLX42_BUILD)
	make -C $(MLX42_BUILD) -j4

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean
	rm -rf $(MLX42_BUILD)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re