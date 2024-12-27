/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:13:07 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 04:13:29 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*concat_env_var(const char *name, const char *value)
{
	char	*env_string;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	env_string = malloc(name_len + value_len + 2);
	if (!env_string)
		return (NULL);
	ft_strlcpy(env_string, name, name_len + value_len + 2);
	ft_strlcat(env_string, "=", name_len + value_len + 2);
	ft_strlcat(env_string, value, name_len + value_len + 2);
	return (env_string);
}
