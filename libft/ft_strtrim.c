/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:27:24 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/23 07:53:37 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimstr(const char *set, const char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		trimleft;
	int		trimright;
	int		len;
	char	*str;

	if (ft_strlen (s1) == 0)
		return (ft_strdup (""));
	trimleft = 0;
	trimright = ft_strlen (s1) - 1;
	while (trimstr (set, s1[trimleft]))
		trimleft++;
	while (trimstr (set, s1[trimright]) && trimright >= 0)
		trimright--;
	if (trimleft > trimright)
		len = trimleft - trimright + 1;
	if (trimleft <= trimright)
		len = trimright - trimleft + 1;
	if (trimright == -1)
		return (ft_strdup (""));
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_memcpy (str, s1 + trimleft, len);
	str[len] = '\0';
	return (str);
}
