/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:06 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/27 09:21:52 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies count characters from the object pointed to by src 
 *to the object pointed to by dest.
 * Both objects are interpreted as arrays of unsigned char.
 *
 * @param void* dest = pointer to the object to copy to
 * @param void* src = pointer to the object to copy from 
 * @param size_t n = number of bytes to copy
 * @return void* =  copy of dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d1;

	if (dest == NULL && src == NULL)
		return (NULL);
	d1 = dest;
	i = 0;
	while (i < n)
	{
		*d1 = *(unsigned char *)(src);
		d1++;
		src++;
		i++;
	}
	return (dest);
}
