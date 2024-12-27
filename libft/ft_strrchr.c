/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 06:27:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/29 17:32:47 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	unsigned int	i;
	char			*tmp;
	char			c;

	c = (char) searchedChar;
	i = 0;
	tmp = NULL;
	if (!ft_isascii(c))
		return ((char *) string);
	while (string[i])
	{
		if (string[i] == c)
			tmp = ((char *)(string + i));
		i++;
	}
	if (c == 0 || !searchedChar)
		return ((char *)(string + i));
	return (tmp);
}
