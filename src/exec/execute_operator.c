/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/04 02:06:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_and(t_ast_node *left,
	t_ast_node *right, t_shell_state *shell_state)
{
	int		status;
	char	*exit_status;

	execute_ast(left, shell_state);
	exit_status = find_env_var(shell_state->env_vars, "?")->value;
	status = ft_atoi(exit_status);
	if (status == 0)
	{
		status = execute_ast(right, shell_state);
	}
}

void	execute_or(t_ast_node *left,
	t_ast_node *right, t_shell_state *shell_state)
{
	int		status;
	char	*exit_status;

	execute_ast(left, shell_state);
	exit_status = find_env_var(shell_state->env_vars, "?")->value;
	status = ft_atoi(exit_status);
	if (status != 0)
	{
		status = execute_ast(right, shell_state);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			set_exit_status(shell_state, WEXITSTATUS(status));
		else
			set_exit_status(shell_state, 1);
	}
}
