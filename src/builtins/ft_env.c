/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/22 19:39:18 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *env_entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(env_entry, '=');
	return (ft_strndup(env_entry, equal_sign - env_entry));
}

char	*get_value(char *env_entry)
{
	char	*equal_sign;
	char	*value;

	value = NULL;
	equal_sign = ft_strchr(env_entry, '=');
	if (!equal_sign || *equal_sign == '\0')
		return (NULL);
	value = ft_strdup(equal_sign + 1);
	return (value);
}

int	ft_env(char **args, t_shell_state *shell_state)
{
	char	**set_args;

	set_args = env_list_to_array(shell_state->env_vars);
	(void)args;
	print_args(set_args);
	free_args(set_args);
	return (0);
}
