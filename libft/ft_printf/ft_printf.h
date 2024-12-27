/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 07:46:27 by nbrigui           #+#    #+#             */
/*   Updated: 2024/08/11 10:35:21 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include "../libft.h"

typedef struct s_formatSpec
{
	int		add_plus;
	int		add_space;
	int		add_hash;
	int		pad_zero;
	int		left_align;
	int		width;
	int		precision;
	int		count;
	char	*tmp;
}				t_formatSpec;
typedef void	(*t_ft_format_handler)(t_formatSpec *, va_list);
typedef struct s_formatHandler
{
	char					*specifier;
	t_ft_format_handler		handler;
	struct s_formatHandler	*next;
}							t_formatHandler;

int				ft_printf(const char *arg0, ...);
t_formatHandler	*ft_lstprintf_new(char *specifier, t_ft_format_handler handler);
void			ft_lstprintf_add_back(t_formatHandler **lst,
					t_formatHandler *new);
void			ft_lstprintf_clear(t_formatHandler **lst, void (*del)(void *));
void			print_padding(int count, char pad_char);
int				ft_max(int a, int b);
int				get_size(t_formatSpec *fs, int strlen);
int				get_number_size(long number, int base);
int				get_size_hexa(t_formatSpec *fs, int strlen);
void			decimal_to_str(int long long value, char *dest, int *sign);
void			add_blank(t_formatSpec *fs, char *dest);
void			add_space_before(t_formatSpec *fs, char *dest,
					int flag_precision);
void			add_space_after(t_formatSpec *fs, char *dest);
int				size_in_base(unsigned int value, char *base);
void			base_to_str(unsigned int value, char *dest, char *base);
void			add_prefix(char *dest, unsigned int value, char *prefix);
void			parse_format_specifiers_precision(const char **p,
					t_formatSpec *fs, va_list args);
void			parse_format_specifiers_width(const char **p, t_formatSpec *fs,
					va_list args);
void			parse_format_specifiers_flags(const char **p, t_formatSpec *fs);
void			is_handler_found(int handler_found, t_formatSpec *fs,
					const char **p);
int				parse_format_specifiers(const char **p, t_formatSpec *fs,
					t_formatHandler *handlers, va_list args);
void			handle_int(t_formatSpec *fs, va_list args);
void			handle_decimal(t_formatSpec *fs, va_list args);
void			handle_char(t_formatSpec *fs, va_list args);
void			handle_string(t_formatSpec *fs, va_list args);
void			handle_pointer(t_formatSpec *fs, va_list args);
void			handle_percent(t_formatSpec *fs, va_list args);
void			handle_void(t_formatSpec *fs, va_list args);
void			handle_hexa(t_formatSpec *fs, va_list args);
void			handle_hexa_upper(t_formatSpec *fs, va_list args);
void			handle_octal(t_formatSpec *fs, va_list args);
void			handle_unsigned(t_formatSpec *fs, va_list args);
#endif
