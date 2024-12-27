/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:51:49 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/22 14:55:28 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
allocates memory for an array of nmemb elements of size bytes each 
and returns a pointer to the allo‐cated  memory.
The  memory is set to zero.  
 If nmemb or size is 0, then calloc() returns either NULL, or a unique pointer
value that can later be successfully passed to free().
 If the multiplication of nmemb and size  would  result  in  integer
 overflow,  then calloc() returns an error.
  By contrast, an integer overflow would not be detected in 
  the following call to malloc(), 
with the result that an incorrectly sized block of memory would be allocated:
size_t = 16711568
*
* @param size_t nmemb
* @param size_t size
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb && size && ((UINT_MAX / size) < nmemb))
		return (NULL);
	p = malloc (nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero (p, nmemb * size);
	return (p);
}
