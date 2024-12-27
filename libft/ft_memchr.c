/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 06:50:09 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/20 09:11:54 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Finds the first occurrence of (unsigned char)c
 *in the initial count bytes (each interpreted as unsigned char) 
 *of the object pointed to by s.
 * @param void* s
 * @param int c
 * @param size_t n
 * @return void* | NULL
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s1[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
