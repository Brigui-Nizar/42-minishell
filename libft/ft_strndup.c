/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/21 12:46:11 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;

	copy = ft_calloc(n + 1, sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_memcpy(copy, s, n);
	return (copy);
}
