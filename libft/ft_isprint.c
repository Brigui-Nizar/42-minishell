/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 07:31:34 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/20 08:59:13 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Check if "c" is printable caractere : ASCII table [32, ..., 126]
 * @param int 
 * @return int 
 * - isprintable ? 1 : 0"
 */
int	ft_isprint(int c)
{
	if (31 < c && c < 127)
		return (1);
	return (0);
}
