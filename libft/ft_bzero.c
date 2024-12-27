/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:37:50 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/26 17:39:44 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * The bzero() function 
 * fills the first "n" bytes of the memory area 
 * pointed to by "s" 
 * with "'\0'".
 * @param void*, size_t
 */
void	ft_bzero(void *s, size_t n)
{
	if (n == 0)
		return ;
	while (n > 0)
	{
		*(unsigned char *)s = '\0';
		n--;
		s++;
	}
	return ;
}
