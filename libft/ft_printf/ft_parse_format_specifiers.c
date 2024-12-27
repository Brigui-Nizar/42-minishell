/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format_specifiers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:20:55 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/16 09:43:30 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	execute_handler_function(const char **p, t_formatSpec *fs,
	t_formatHandler *handlers, va_list args)
{
	int	handler_found;

	handler_found = 0;
	while (handlers->next != NULL)
	{
		if (ft_strncmp (handlers->specifier, p[0], 3) == 0)
		{
			handlers->handler(fs, args);
			(*p) += 2;
			handler_found = 1;
			break ;
		}
		else if (ft_strncmp (handlers->specifier, p[0], 1) == 0)
		{
			handlers->handler(fs, args);
			handler_found = 1;
			(*p) += 1;
			break ;
		}
		handlers = handlers->next;
	}
	is_handler_found(handler_found, fs, p);
	return (0);
}

// Fonction pour analyser les spécificateurs de format
int	parse_format_specifiers(const char **p, t_formatSpec *fs,
	t_formatHandler *handlers, va_list args)
{
	fs->precision = -1;
	fs->add_plus = -1;
	fs->add_space = 0;
	fs->add_hash = 0;
	fs->pad_zero = 0;
	fs->left_align = 0;
	fs->width = 0;
	parse_format_specifiers_flags(&*p, fs);
	parse_format_specifiers_width(&*p, fs, args);
	parse_format_specifiers_precision(&*p, fs, args);
	execute_handler_function(&*p, fs, handlers, args);
	return (0);
}
