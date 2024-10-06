# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 03:44:02 by kael-ala          #+#    #+#              #
#    Updated: 2024/10/06 01:43:33 by kael-ala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -f


M_FILES = ./src/main.c ./src/parse.c 

INCS = ./libft/libft.h

libft = ./libft/libft.a

M_OBJ = $(M_FILES:.c=.o)

all : $(NAME)

$(NAME) :  $(P_OBJ) $(M_OBJ) $(libft)
	$(CC) $(FLAGS) $(libft) $^ -o $(NAME)

$(M_OBJ) : ./includes/cub3d.h

%.o : %.c $(INCS)
	$(CC) $(FLAGS) -c $< -o $@
$(libft) :
	make -C ./libft
clean:
	$(RM) $(P_OBJ) $(M_OBJ) $(B_OBJ)
	make -C ./libft clean
fclean: clean
	$(RM) $(P_OBJ) $(M_OBJ) $(B_OBJ) $(NAME) $(BNAME)
	make -C ./libft fclean
re: fclean all