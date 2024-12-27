/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_memory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:52:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 04:21:53 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error_copy_env(t_shell_state *shell_state)
{
	minishell_error_status_code("minishell: Failed to copy environment NULL.",
		EXIT_FAILURE, shell_state);
}

void	minishell_exit_error_calloc(t_shell_state *shell_state)
{
	minishell_error_status_code("Failed to allocate memory.",
		EXIT_FAILURE, shell_state);
	exit(EXIT_FAILURE);
}

void	minishell_exit_error_strdup(t_shell_state *shell_state)
{
	minishell_error_status_code("Failed to duplicate string.",
		EXIT_FAILURE, shell_state);
	exit(EXIT_FAILURE);
}

void	minishell_error_errno(t_shell_state *shell_state)
{
	minishell_error_status_code(strerror(errno), EXIT_FAILURE, shell_state);
}

void	minishell_error_pipe(t_shell_state *shell_state)
{
	minishell_error_status_code("Failed to create pipe.",
		EXIT_FAILURE, shell_state);
}
