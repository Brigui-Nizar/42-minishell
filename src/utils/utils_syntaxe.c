/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:54:49 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 07:26:21 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_one_char(char *str)
{
	if (ft_strlen(str) == 1 && ft_strchr("<>", str[0]))
		return (1);
	return (0);
}

int	is_two_char(char *str)
{
	if (ft_strlen(str) == 2 && ft_strnstr("><\n", str, 2))
		return (1);
	return (0);
}
