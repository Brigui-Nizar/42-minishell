/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:09:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/30 11:09:59 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Check if "c" is alpha && uppercase
 * @param int 
 * @return int 
 * - isuppercase ? 1 : 0"
 */
static int	ft_isupper(int c)
{
	if (64 < c && c < 91)
		return (1);
	return (0);
}

/*
 * Check if "c" is alpha && lowercase
 * @param int 
 * @return int 
 * - islowercase ? 1 : 0"
 */
static int	ft_islower(int c)
{
	if (96 < c && c < 123)
		return (1);
	return (0);
}

/*
 * Check if "c" is alpha
 * @param int 
 * @return int 
 * - isalpha ? 1 : 0"
 */
int	ft_isalpha(int c)
{
	if (ft_isupper (c) == 1)
		return (1);
	if (ft_islower (c) == 1)
		return (1);
	return (0);
}
