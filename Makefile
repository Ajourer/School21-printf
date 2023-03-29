# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralverta <ralverta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 15:40:50 by ralverta          #+#    #+#              #
#    Updated: 2021/01/28 18:41:09 by ralverta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c \
        parsing.c \
        char_proc.c \
        string_proc.c \
        int_proc.c \
        unsign_proc.c \
        hex_proc.c \
        pointer_proc.c \
        ft_u_itoa.c \
        ft_itoa_base.c \
        ft_printf_utils.c

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra

FT = libft.a
FTDIR = libft/

all: $(NAME)
$(NAME): $(OBJ) $(FTDIR)$(FT)
	ar rc $(NAME) $(OBJ)

$(FTDIR)$(FT):
	$(MAKE) -C $(FTDIR)
	cp $(FTDIR)$(FT) $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(FTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FTDIR) fclean

re: fclean all

.PHONY: re all clean fclean
