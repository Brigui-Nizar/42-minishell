/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/22 19:40:25 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Fonction ft_set pour afficher les variables d'environnement et locales
*/
int	ft_set(char **args, t_shell_state *shell_state)
{
	char	**set_args;

	set_args = set_list_to_array(shell_state->env_vars);
	(void)args;
	print_args(set_args);
	free_args(set_args);
	return (0);
}

void	update_set(t_shell_state *shell_state, char *key, char *value)
{
	set_env_var(&shell_state->env_vars, key, value, 0);
}
