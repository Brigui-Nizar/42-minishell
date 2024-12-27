/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:52:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/05 19:17:49 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error_export(char *cmd, t_shell_state *shell_state)
{
	(void)shell_state;
	ft_putstr_fd("minishell:  export: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	set_exit_status(shell_state, 1);
}

void	minishell_error_cmd_not_found(char *cmd, t_shell_state *shell_state)
{
	char	*exit_status;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit_status = ft_itoa(127);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
}

void	minishell_error_no_such_file_or_directory(char *dir,
	t_shell_state *shell_state)
{
	char	*exit_status;

	ft_putstr_fd("minishell: cd:", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	exit_status = ft_itoa(1);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
}

void	minishell_error_too_many_args(char *cmd, t_shell_state *shell_state)
{
	char	*exit_status;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	exit_status = ft_itoa(1);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
}

void	minishell_error_exit_no_path(void)
{
	minishell_error("PATH not found in environment");
	exit(EXIT_FAILURE);
}
