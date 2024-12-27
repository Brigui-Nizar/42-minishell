/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:52:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 04:24:24 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error(char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	minishell_error_status_code(char *message,
	int status_code, t_shell_state *shell_state)
{
	char	*exit_status;

	exit_status = ft_itoa(status_code);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
	minishell_error(message);
}
