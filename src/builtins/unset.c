/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 04:04:48 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function unsets the environment variable
*/
int	ft_unset(char **args, t_shell_state *shell_state)
{
	if (!args || !args[0] || !args[1])
		return (1);
	unset_env_var(&shell_state->env_vars, args[1]);
	return (0);
}

void	unset_env_var(t_env_var **head, const char *name)
{
	t_env_var	*current;
	t_env_var	*prev ;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
