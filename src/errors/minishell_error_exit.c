/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:29:12 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/08 15:01:51 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error_exit_is_directory(char *cmd,
	t_shell_state *shell_state)
{
	(void)shell_state;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	exit(126);
}

void	minishell_error_exit_no_such_file_or_directory(char *cmd,
	t_shell_state *shell_state)
{
	(void)shell_state;
	perror("execve failed");
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": no such file or directory\n", STDERR_FILENO);
	exit(127);
}

void	minishell_error_exit_no_permission_denied(char *cmd,
	t_shell_state *shell_state)
{
	(void)shell_state;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(":  Permission denied\n", STDERR_FILENO);
	exit(126);
}

void	minishell_error_exit_num_args(char **args,
	t_shell_state *shell_state)
{
	(void)shell_state;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_split(args);
	exit_shell(shell_state, 2);
	exit(2);
}
