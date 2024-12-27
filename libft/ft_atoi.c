/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:18:46 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/30 11:08:13 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

/*
* Convert a string to integer.
* Remove all whitespace
* @param char* 
* @return int
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	total;
	int	sign;

	i = 0;
	total = 0;
	sign = 1;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		total = (total * 10) + (str[i] - 48);
		i++;
	}
	return (sign * total);
}
