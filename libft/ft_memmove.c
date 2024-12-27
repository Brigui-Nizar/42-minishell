/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 10:49:37 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/27 10:26:20 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies n characters from the object pointed to by src 
 *to the object pointed to by dest.
 * Both objects are interpreted as arrays of unsigned char.
 * The objects may overlap: 
 *copying takes place as if the characters were copied 
 to a temporary character array 
 and then the characters were copied from the array to dest.
 *
 * @param void* dest = pointer to the object to copy to
 * @param void* src = pointer to the object to copy from 
 * @param size_t n = number of bytes to copy
 * @return void* =  copy of dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dest;
	s = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
		return (dest);
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
