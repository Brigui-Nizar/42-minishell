/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:35:49 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/06 19:28:43 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	size_in_base(unsigned int value, char *base)
{
	int	count;

	count = 0;
	if (value == 0)
		return (1);
	while (value > 0)
	{
		value /= (int) ft_strlen(base);
		count++;
	}
	return (count);
}

void	base_to_str(unsigned int value, char *dest, char *base)
{
	if (value > 0)
	{
		base_to_str(value / (int) ft_strlen(base), dest - 1, base);
		*dest = (char)base[value % 16];
	}
}
