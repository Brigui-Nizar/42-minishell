/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:40:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/18 14:04:41 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	precision(t_formatSpec *fs, char *dest,
	int *flag_precision, int value)
{
	size_t	diff;

	if (value < 0)
	{
		if ((int) ft_strlen(dest) >= fs->precision)
		{
			*flag_precision = ' ';
			return ;
		}
	}
	if (fs->precision > 0 && fs->precision > (int) ft_strlen(dest))
	{
		*flag_precision = '0';
		diff = fs->precision - ft_strlen(dest);
		ft_memmove(dest + diff, dest, (int) ft_strlen(dest) + 1);
		ft_memset(dest, flag_precision[0], diff);
		*flag_precision = ' ';
	}
	else
		*flag_precision = ' ';
	if (fs->precision == 0 && value == 0)
		ft_memset(dest, 0, 1);
	if (fs->precision == -1)
		*flag_precision = ' ';
}

static void	add_zero(t_formatSpec *fs, char *dest, int value)
{
	size_t	diff;
	int		len;
	int		sign;

	sign = 0;
	if (value < 0)
		sign = 1;
	len = ft_strlen (dest);
	if (value > 0 && fs->add_plus == 1)
		sign = 1;
	if (value > 0 && fs->add_space == 1)
		sign ++;
	if (fs->pad_zero > 0 && fs->width - sign > len)
	{
		diff = fs->width - sign - ft_strlen(dest);
		ft_memmove(dest + diff, dest, len + 1);
		ft_memset(dest, '0', diff);
	}
}

static void	add_sign_before(t_formatSpec *fs, char *dest, int value)
{
	int	len;

	len = ft_strlen(dest);
	if (value < 0)
	{
		ft_memmove(dest + 1, dest, len + 1);
		ft_memset(dest, '-', 1);
	}
	else if (fs->add_plus > 0)
	{
		ft_memmove(dest + 1, dest, len + 1);
		ft_memset(dest, '+', 1);
	}
}

static char	*set_dest_int(t_formatSpec *fs, int value, int *sign)
{
	int		strlen;
	int		total_size;
	char	*dest;

	strlen = get_number_size(value, 10);
	total_size = get_size(fs, strlen);
	dest = ft_calloc(total_size + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	decimal_to_str (value, dest + strlen - 1, sign);
	if (value == 0 && (fs->precision == 0 || fs->precision == -1))
		dest[0] = '0';
	return (dest);
}

void	handle_decimal(t_formatSpec *fs, va_list args)
{
	int		value;
	int		sign;
	char	*dest;
	int		*flag_precision;
	int		c;

	c = ' ';
	flag_precision = &c;
	sign = 0;
	value = va_arg (args, int);
	dest = set_dest_int(fs, value, &sign);
	if (!dest)
		return ;
	precision (fs, dest, flag_precision, value);
	if (!fs->precision || fs->precision == -1)
		add_zero (fs, dest, value);
	add_sign_before (fs, dest, value);
	if (!sign)
		add_blank (fs, dest);
	add_space_before (fs, dest, c);
	add_space_after (fs, dest);
	write (1, dest, ft_strlen(dest));
	fs->count += ft_strlen(dest);
	free (dest);
}
