/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 09:04:25 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/20 09:49:21 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * fills the first n bytes of the memory area 
 * pointed to by s 
 * with the constant byte c.
 * return s
 *
 * @param void* s = pointer to the object to fill
 * @param c = fill byte  
 * @param size_t n = number of bytes to fill 
 * @return void* =  copy of dest
 */
void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n > 0)
	{
		*str = (unsigned char)c;
		str++;
		n--;
	}
	return (s);
}
