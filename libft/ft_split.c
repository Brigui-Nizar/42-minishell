/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:14:18 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/15 00:09:10 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Alloue (avec malloc(3)) et retourne un tableau
de chaînes de caractères obtenu en séparant ’s’ à
l’aide du caractère ’c’, utilisé comme délimiteur.
Le tableau doit être terminé par NULL
*/
static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		if (s[i] == '\0')
			return (count);
		i++;
	}
	return (count);
}

static int	trimindex(int i, char const *s, char c)
{
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	getsize(int i, char const *s, char c)
{
	int	trim;

	trim = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		trim ++;
		i++;
	}
	return (trim);
}

int	freelist(int w, char **p)
{
	if (p[w] == NULL)
	{
		w--;
		while (w > 0)
		{
			free (p[w]);
			w--;
		}
		free (p[0]);
		free (p);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		size;
	int		i;
	int		w;
	int		len;

	p = ft_calloc ((ft_countwords (s, c) + 1), sizeof(char *));
	if (p == NULL)
		return (NULL);
	i = 0;
	w = 0;
	len = ft_strlen(s);
	while (s && i < len && s[i] && w < ft_countwords (s, c))
	{
		size = getsize(i, s, c);
		i = trimindex(i, s, c);
		p[w] = ft_substr(s + (i - size), 0, size);
		if (freelist (w, p))
			return (NULL);
		w++;
		i++;
	}
	p[w] = NULL;
	return (p);
}
