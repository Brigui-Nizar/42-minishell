/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 07:13:41 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/20 08:55:53 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Check if "c" is ascii caractere
 * @param int 
 * @return int 
 * - isascii ? 1 : 0"
 */
int	ft_isascii(int c)
{
	if (0 <= c && c < 128)
		return (1);
	return (0);
}
