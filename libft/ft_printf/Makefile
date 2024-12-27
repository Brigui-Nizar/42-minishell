# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:33:56 by nbrigui           #+#    #+#              #
#    Updated: 2024/06/14 13:52:50 by nbrigui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c \
		ft_lstprintf.c \
		ft_parse_format_specifiers.c \
		utils_numbers.c \
		common.c \
		base.c \
		ft_printf_parse_format.c \
		ft_handle_int.c \
		ft_handle_decimal.c\
		ft_handle_char.c \
		ft_handle_string.c \
		ft_handle_percent.c \
		ft_handle_pointer.c \
		ft_handle_hexa.c \
		ft_handle_hexa_upper.c \
		ft_handle_octal.c \
		ft_handle_void.c  \
		ft_handle_unsigned.c 


NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror -fPIE

CC = cc

OBJS =	${SRCS:c=o}


HEADER = -I ./libft # include libft.h
LIBFT = -L ./libft # include librairie libft.a : -lft = libft.a

all: $(NAME) 

${NAME}: ${OBJS}
	ar rcs $(NAME) $(OBJS)

bonus: ${OBJS}
	@ar rcs $(NAME) $(OBJS)

${OBJS}: ${SRCS}
	make -C libft/
	@cp libft/libft.a .
	@cp libft/libft.h .
	@mv libft.a $(NAME)
	$(CC) $(CFLAGS) -c ${SRCS} $(HEADER)

clean :
	rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}
		rm -f test
		rm -f main.o
		rm -f libft.h
		rm -f libft.a
		make fclean -C ./libft/

re: fclean all

.PHONY:	all clean fclean re bonus test

test:  $(OBJS) 
	cc  $(HEADER) -c main.c 
	cc -o test main.o $(OBJS) $(LIBFT) -lft


norminette:
	norminette ${SRCS}

