/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:41:29 by nbrigui           #+#    #+#             */
/*   Updated: 2024/05/30 11:29:16 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

/*
Alloue (avec malloc(3)) et retourne une chaîne de
caractères issue de la chaîne ’s’.
Cette nouvelle chaîne commence à l’index ’start’ et
a pour taille maximale ’len’.

retour NULL si l’allocation échoue.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;

	if (s == NULL)
		return (ft_strdup(""));
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc (sizeof (char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy (str, s + start, len + 1);
	return (str);
}
