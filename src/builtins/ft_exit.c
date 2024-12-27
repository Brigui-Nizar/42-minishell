/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:47:44 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:47:47 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long	ft_atol(const char *str);
int		is_valid_long(const char *str);
void	close_fds(t_shell_state *shell_state);

int	ft_exit(char **args, t_shell_state *shell_state)
{
	int		status_code;

	status_code = EXIT_SUCCESS;
	if (args[1] != NULL)
	{
		if (!is_valid_long(args[1]))
			minishell_error_exit_num_args(args, shell_state);
		if (args_len(args) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			status_code
				= ft_atol(find_env_var(shell_state->env_vars, "?")->value);
			if (status_code == 0)
				status_code = 1;
			return (256 * status_code);
		}
		status_code = ft_atol(args[1]);
	}
	else
		status_code = ft_atol(find_env_var(shell_state->env_vars, "?")->value);
	free_split(args);
	rl_clear_history();
	close_fds(shell_state);
	exit_shell(shell_state, status_code);
	exit(status_code);
}
