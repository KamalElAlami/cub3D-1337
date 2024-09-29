# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kael-ala <kael-ala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 03:44:02 by kael-ala          #+#    #+#              #
#    Updated: 2024/09/29 05:44:08 by kael-ala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f


M_FILES = ./src/main.c ./src/parse.c

INCS = ./Libft-1337/libft.h

libft = ./Libft-1337/libft.a

M_OBJ = $(M_FILES:.c=.o)

all : $(NAME)

$(NAME) :  $(P_OBJ) $(M_OBJ) $(libft)
	$(CC) $(FLAGS) $(libft) $^ -o $(NAME)

$(M_OBJ) : ./includes/cub3d.h

%.o : %.c $(INCS)
	$(CC) $(FLAGS) -c $< -o $@
$(libft) :
	make -C ./Libft-1337
clean:
	$(RM) $(P_OBJ) $(M_OBJ) $(B_OBJ)
	make -C ./Libft-1337 clean
fclean: clean
	$(RM) $(P_OBJ) $(M_OBJ) $(B_OBJ) $(NAME) $(BNAME)
	make -C ./Libft-1337 fclean
re: fclean all