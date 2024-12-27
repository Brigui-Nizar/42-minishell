/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:40:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/12 17:47:43 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_number_u_size(long number)
{
	int	size;

	size = 0;
	if (number < 0)
		number = -number;
	if (number == 0)
		size++;
	while (number != 0)
	{
		size ++;
		number = number / 10;
	}
	return (size);
}

static void	unsigned_int_to_str(unsigned int value, char *dest)
{
	if (value >= 10)
	{
		*dest = (char) '0' + (value % 10);
		unsigned_int_to_str(value / 10, dest - 1);
	}
	else if (value)
	{
		*dest = (char) '0' + (value);
	}
}

static void	precision(t_formatSpec *fs, char *dest, int value)
{
	size_t	diff;
	int		len;

	len = ft_strlen(dest);
	if (fs->precision > 0 && fs->precision > len)
	{
		diff = fs->precision - ft_strlen(dest);
		ft_memmove(dest + diff, dest, len + 1);
		ft_memset(dest, '0', diff);
	}
	if (fs->precision == 0 && value == 0)
		ft_memset(dest, 0, 1);
}

static void	add_zero(t_formatSpec *fs, char *dest)
{
	size_t	diff;
	int		len;

	len = ft_strlen(dest);
	if (fs->pad_zero > 0 && fs->width > len)
	{
		diff = fs->width - ft_strlen(dest);
		ft_memmove (dest + diff, dest, len + 1);
		ft_memset (dest, '0', diff);
	}
}

void	handle_unsigned(t_formatSpec *fs, va_list args)
{
	unsigned int	value;
	int				strlen;
	int				total_size;
	char			*dest;

	value = va_arg(args, int);
	strlen = get_number_u_size(value);
	total_size = get_size(fs, strlen);
	dest = calloc(total_size + 1, sizeof(char));
	if (fs->precision != 0)
		unsigned_int_to_str(value, dest + strlen - 1);
	if (dest == NULL)
		return ;
	unsigned_int_to_str(value, dest + strlen - 1);
	if (value == 0 && (fs->precision == 0 || fs->precision == -1))
		dest[0] = '0';
	add_blank(fs, dest);
	precision(fs, dest, value);
	if (!fs->precision || fs->precision == -1)
		add_zero(fs, dest);
	add_space_before(fs, dest, ' ');
	add_space_after(fs, dest);
	write(1, dest, ft_strlen(dest));
	fs->count += ft_strlen(dest);
	free(dest);
}
