/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:40:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/18 14:53:18 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_char(t_formatSpec *fs, va_list args)
{
	char	value;
	int		len;

	value = (char) va_arg(args, int);
	len = 1;
	if (fs->precision > 0 && fs->precision < len)
		len = fs->precision;
	if ((len > 1 || fs->width > len) && !fs->left_align)
	{
		print_padding(fs->width - len, ' ');
		fs->count = (fs->count + fs->width - len);
	}
	fs->count = (fs->count + 1);
	write(1, &value, 1);
	if (fs->left_align == 1)
	{
		print_padding(fs->width - len, ' ');
		fs->count = (fs->count + fs->width - len);
	}
}
