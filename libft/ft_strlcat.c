/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 04:03:45 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/22 14:54:07 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
size_t strlcat (char * dst, const char * src, size_t siz)
       Concatenate two strings. Appends src to string dst of size siz 
	   (unlike strncat(), siz is the full size
       of dst, not space left). At most siz-1 characters will be copied. 
	   Always NULL terminates (unless siz
       <= strlen(dst)).

       Returns
           The strlcat() function 
		   returns strlen(src) + MIN(siz, strlen(initial dst)). 
		   If retval >= siz,  truncation occurred.

       Appends src to string dst of size siz 
	   (unlike strncat(), siz is the full size of dst, not space left).
       At most siz-1 characters will be copied. 
	   Always NULL terminates (unless siz <= strlen(dst)).

       Returns
           The strlcat() function 
		   returns strlen(src) + MIN(siz, strlen(initial dst)). 
		   If retval >= siz, truncation occurred.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen (dst);
	src_len = ft_strlen (src);
	if (size <= dest_len)
		dest_len = size;
	if (size == dest_len)
	{
		return (size + src_len);
	}
	if (src_len < size - dest_len)
		ft_memcpy (dst + dest_len, src, (src_len + 1));
	else
	{
		ft_memcpy (dst + dest_len, src, (size - dest_len - 1));
		dst[size - 1] = '\0';
	}
	return (dest_len + src_len);
}
