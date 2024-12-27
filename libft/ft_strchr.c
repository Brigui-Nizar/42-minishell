/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 04:47:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/29 17:33:29 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Finds the first occurrence of the null-terminated byte string  pointed to by 
 searchedChar in the null-terminated byte string pointed to by "str".
  The terminating null characters are not compared.
 *
 * @param char* str = pointer to the null-terminated byte string to examine
 * @param int searchedChar =
 *  pointer to the null-terminated byte string to search for 
 * 
 * @return char* =  
 * Pointer to the first character of the found substring in str, 
 * or a null pointer if such substring is not found. 
 * If searchedChar points to an empty string, str is returned. 
 *
 */
char	*ft_strchr(const char *string, int searchedChar)
{
	unsigned int	i;
	char			c;

	c = (char) searchedChar;
	i = 0;
	if (!ft_isascii(c))
		return ((char *) string);
	while (string[i])
	{
		if (string[i] == c)
			return ((char *)(string + i));
		i++;
	}
	if (c == 0 || !c)
		return ((char *)(string + i));
	return (NULL);
}
