/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:58:19 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/18 14:58:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

int	get_size(t_formatSpec *fs, int strlen)
{
	int	temp;
	int	count;

	temp = 0;
	count = strlen;
	if (fs->add_hash && strlen > 0)
		count += 2;
	if (fs->add_plus && strlen > 0)
		count ++;
	temp = ft_max (fs->precision, fs->width);
	count += ft_max (temp, strlen);
	return (count);
}

int	get_number_size(long number, int base)
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
		number = number / base;
	}
	return (size);
}

void	decimal_to_str(int long long value, char *dest, int *sign)
{
	if (value < 0)
	{
		value = -value;
		*sign = 1;
	}
	if (value >= 10)
	{
		*dest = (char) '0' + (value % 10);
		decimal_to_str(value / 10, dest - 1, sign);
	}
	else if (value)
	{
		*dest = (char) '0' + (value);
	}
}

int	get_size_hexa(t_formatSpec *fs, int strlen)
{
	int	temp;
	int	count;

	temp = 0;
	count = strlen;
	if (fs->add_hash && strlen > 0)
		count += 2;
	temp = ft_max(fs->precision, fs->width);
	count += ft_max(temp, strlen);
	return (count);
}
