# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:33:56 by nbrigui           #+#    #+#              #
#    Updated: 2024/09/24 13:05:14 by nbrigui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
AR = ar rcs
SRC =	ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_strlen \
		ft_memset \
		ft_bzero \
		ft_memcpy \
		ft_memmove \
		ft_strlcpy \
		ft_strlcat \
		ft_tolower \
		ft_toupper \
		ft_strchr \
		ft_strcat \
		ft_strcpy \
		ft_strrchr \
		ft_strncmp \
		ft_strcmp \
		ft_strnstr \
		ft_memchr \
		ft_memcmp \
		ft_atoi \
		ft_calloc \
		ft_strdup \
		ft_strndup \
		ft_substr \
		ft_strjoin \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_striteri \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		get_next_line
	
BONUS_SRC = ft_lstnew \
	ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap  
PRINTF_SRC = ft_printf/ft_printf \
		ft_printf/ft_lstprintf \
		ft_printf/ft_parse_format_specifiers \
		ft_printf/utils_numbers \
		ft_printf/common \
		ft_printf/base \
		ft_printf/ft_printf_parse_format \
		ft_printf/ft_handle_int \
		ft_printf/ft_handle_decimal \
		ft_printf/ft_handle_char \
		ft_printf/ft_handle_string \
		ft_printf/ft_handle_percent \
		ft_printf/ft_handle_pointer \
		ft_printf/ft_handle_hexa \
		ft_printf/ft_handle_hexa_upper \
		ft_printf/ft_handle_octal \
		ft_printf/ft_handle_void  \
		ft_printf/ft_handle_unsigned

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))
BONUS_SRCS = $(addsuffix .c, $(BONUS_SRC))
BONUS_OBJS = $(addsuffix .o, $(BONUS_SRC))
PRINTF_SRCS = $(addsuffix .c, $(PRINTF_SRC))
PRINTF_OBJS = $(addsuffix .o, $(PRINTF_SRC))

%.o: %.c $(SRCS) $(BONUS_SRCS) $(PRINTF_SRCS)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(PRINTF_OBJS)
	@$(AR) $@ $^
	@echo "Libft ready."

bonus: $(OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $^
	@echo "Libft + bonus ready."

all: $(NAME)

clean:
	@rm -f *.o
	@rm -f ft_printf/*.o
	@echo "Libft: removed .o object files."

fclean: clean
	@rm -f $(NAME)
	@echo "Libft: removed libft.a file."

re: clean all

.PHONY: all clean fclean re bonus