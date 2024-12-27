/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:39:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:47:12 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **args, t_shell_state *shell_state)
{
	char		*cwd;
	t_env_var	*env_var;

	(void)args;
	env_var = find_env_var(shell_state->env_vars, "PWD");
	if (env_var == NULL)
	{
		perror("getcwd");
		return (1);
	}
	cwd = env_var->value;
	printf("%s\n", cwd);
	return (0);
}
