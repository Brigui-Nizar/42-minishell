/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:43:44 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/20 08:54:59 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Check if "c" is alphanumeric
 * @param int 
 * @return int 
 * - isalphanumeric ? 1 : 0"
 */
int	ft_isalnum(int c)
{
	if (ft_isalpha (c))
		return (1);
	if (ft_isdigit (c))
		return (1);
	return (0);
}
