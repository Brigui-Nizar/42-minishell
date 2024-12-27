/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:25:31 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/22 14:51:23 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The strnstr() function locates the first occurrence of the null-terminated 
string little in the string big, where not more than len characters are searched.
  Characters that appear after a ‘\0’ character are not searched.

If little is an empty string, big is returned;
 if little occurs nowhere in big, NULL is returned; 
 otherwise a pointer to the first character of the 
 first occurrence of little is returned.

#include <bsd/string.h>
@TODO a corriger
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0' || little == NULL)
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[0])
		{
			while (big[i + j] && big[i + j] == little[j] && i + j < len)
			{
				j++;
			}
			if (little[j] == '\0')
				return ((char *) big + i);
		}
		i++;
	}
	return (NULL);
}
