/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 04:40:37 by nbrigui           #+#    #+#             */
/*   Updated: 2024/08/11 10:21:51 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Fonction pour analyser la precision
 */
void	parse_format_specifiers_precision(const char **p, t_formatSpec *fs,
	va_list args)
{
	int	value;

	if (**p == '.')
	{
		(*p)++;
		fs->precision = 0;
		while (**p >= '0' && **p <= '9')
		{
			fs->precision = fs->precision * 10 + (**p - '0');
			(*p)++;
		}
		if (**p == '*')
		{
			value = va_arg(args, int);
			fs->precision = value;
			(*p)++;
		}
	}
}

/*
 Analyse de la largeur de champ
*/
void	parse_format_specifiers_width(const char **p, t_formatSpec *fs,
	va_list args)
{
	fs->width = 0;
	while (**p >= '0' && **p <= '9')
	{
		fs->width = fs->width * 10 + (**p - '0');
		(*p)++;
	}
	if (**p == '*')
	{
		fs->width = va_arg(args, int);
		(*p)++;
	}
}

/*
Fonction pour analyser les flags
*/
void	parse_format_specifiers_flags(const char **p, t_formatSpec *fs)
{
	while (**p == '+' || **p == ' ' || **p == '#' || **p == '0' || **p == '-')
	{
		if (**p == '+')
			fs->add_plus = 1;
		if (**p == ' ')
			fs->add_space = 1;
		if (**p == '#')
			fs->add_hash = 1;
		if (**p == '0')
			fs->pad_zero = 1;
		if (**p == '-')
			fs->left_align = 1;
		(*p)++;
	}
}

void	is_handler_found(int handler_found, t_formatSpec *fs, const char **p)
{
	if (handler_found == 0)
	{
		while (**p != '%')
			(*p)--;
		ft_putchar_fd (**p, 1);
		fs->count = fs->count + 1;
		(*p) += 1;
	}
}
