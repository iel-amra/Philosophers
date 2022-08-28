# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iel-amra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 13:22:25 by iel-amra          #+#    #+#              #
#    Updated: 2022/08/17 13:29:06 by iel-amra         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
SRC=addons.c ft_abs.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstget.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c ft_printf_def.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c get_next_line_utils.c print_big_hexa.c print_char.c print_hexa.c print_int.c print_little_hexa.c print_pointer.c print_pourcentage.c print_string.c print_unsigned_int.c psf.c spaces.c
OBJ=$(SRC:.c=.o)
HEADER=libft.h

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)

%o : %c $(HEADER)
	gcc -c -Werror -Wall -Wextra $<
	
clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)

.SUFFIXES:

.PHONY : clean fclean all re
