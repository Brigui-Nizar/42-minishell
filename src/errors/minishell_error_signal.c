/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_signal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:05:40 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:46:42 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error_signal(int status, t_shell_state *shell_state)
{
	char	*exit_status;

	exit_status = NULL;
	if (WTERMSIG(status) == SIGKILL)
		ft_putstr_fd("Killed: 9\n", 2);
	else if (WTERMSIG(status) == SIGTERM)
		ft_putstr_fd("Terminated: 15\n", 2);
	exit_status = ft_itoa(128 + WTERMSIG(status));
	update_set(shell_state, "?", exit_status);
	free(exit_status);
}
