# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarif <sarif@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/23 18:14:53 by kael-ala          #+#    #+#              #
#    Updated: 2024/11/29 22:04:48 by sarif            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

FILES = ft_striteri.c ft_memcmp.c  ft_bzero.c ft_putnbr_fd.c ft_strmapi.c ft_itoa.c \
	ft_putendl_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_strtrim.c ft_strjoin.c ft_strdup.c \
	ft_calloc.c  ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memchr.c ft_memset.c ft_memcpy.c \
	ft_strlen.c ft_strncmp.c ft_strlcat.c ft_strlcpy.c ft_atoi.c \
	ft_strchr.c ft_strrchr.c ft_strnstr.c \
	ft_tolower.c ft_toupper.c ft_memmove.c ft_split.c \
	ft_substr.c get_next_line.c tax_collector.c ft_itoa_base.c \

OBJ = $(FILES:.c=.o)

AR = ar rc

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY : clean 