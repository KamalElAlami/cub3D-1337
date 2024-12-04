# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 03:44:02 by kael-ala          #+#    #+#              #
#    Updated: 2024/12/04 17:04:27 by sarif            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BNAME = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

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
SRCS = mandatory/src/main.c mandatory/parse/parse.c mandatory/parse/parse_utilities.c mandatory/textures/graphics.c mandatory/parse/utilities.c mandatory/src/raycasting.c mandatory/src/raycasting_utils.c mandatory/parse/parse_utils1.c mandatory/parse/parse_utils2.c mandatory/src/game_control.c mandatory/textures/textures.c

# Sources
BSRCS = bonus/src/main.c bonus/parse/parse.c bonus/parse/parse_utilities.c bonus/textures/graphics.c bonus/parse/utilities.c bonus/src/raycasting.c bonus/src/raycasting_utils.c bonus/parse/parse_utils1.c bonus/parse/parse_utils2.c bonus/src/game_control.c

# Objects
OBJS = $(SRCS:.c=.o)
# Objects
BOBJS = $(BSRCS:.c=.o)

# Libraries
#LIBS = $(MLX42_LIB) $(LIBFT) -lglfw -L ~/.brew/Cellar/glfw/3.4/lib/
LIBS = $(MLX42_LIB) $(LIBFT) -lglfw -L /opt/homebrew/Cellar/glfw/3.4/lib/

all: $(NAME)

$(NAME): $(MLX42_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus: $(BNAME)

$(BNAME): $(MLX42_LIB) $(LIBFT) $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) $(LIBS) -o $(BNAME)

%.o: %.c ./includes/cub3d.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX42_LIB):
	cmake $(MLX42_PATH) -B $(MLX42_BUILD)
	make -C $(MLX42_BUILD) -j4

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(OBJS) $(BOBJS)
	make -C $(LIBFT_PATH) clean
	rm -rf $(MLX42_BUILD)

fclean: clean
	rm -f $(NAME) $(BNAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re