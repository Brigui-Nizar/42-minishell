/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:11:11 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 09:26:36 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Compares the first count bytes of the objects pointed to by lhs and rhs. 
 *The comparison is done lexicographically.
 * The sign of the result is the sign of the difference between the 
 *values of the first pair of bytes (both interpreted as unsigned char) 
 *that differ in the objects being compared. 
 *
 * @param void* s1 = pointers to the objects to compare
 * @param void* s2 = pointers to the objects to compare
 * @param size_t n = number of bytes to examine 
 * @return int = str1[i] - str2[i]
 * 
 * 
	char s[] = {-128, 0, 127, 0};
	char sCpy[] = {-128, 0, 127, 0};
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
