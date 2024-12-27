/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:45:24 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 09:25:09 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getsize(long n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size ++;
		n = -n;
	}
	if (n == 0)
		size++;
	while (n != 0)
	{
		size ++;
		n = n / 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;
	long	number;

	number = (long)n;
	if (number == 0)
		return (ft_strdup("0"));
	size = getsize (number);
	str = malloc (sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	if (number < 0)
	{
		number = -number;
		str[0] = '-';
	}
	str[size] = '\0';
	size --;
	while (size >= 0 && number != 0)
	{
		str[size] = '0' + (number % 10);
		number = (number / 10);
		size --;
	}
	return (str);
}
