/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:19:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:47:19 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_shell_state *shell_state);

int	execute_handler_function(char **p, t_formatHandler *handlers,
	t_shell_state *shell_state)
{
	int		status;

	status = 0;
	while (handlers != NULL)
	{
		if (ft_strlen(handlers->cmd) != ft_strlen(p[0]))
		{
			handlers = handlers->next;
			continue ;
		}
		if (ft_strcmp (handlers->cmd, p[0]) == 0)
		{
			status = handlers->handler(p, shell_state);
			free(shell_state->prompt);
			free(shell_state->minishell_path);
			ft_lst_builtins_clear(&shell_state->handlers, free);
			lst_clear_env(shell_state->env_vars);
			rl_clear_history();
			close_fds(shell_state);
			return (status);
		}
		handlers = handlers->next;
	}
	return (1);
}
