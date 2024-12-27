/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 04:42:07 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* check if the path is a file or a directory
* return 1 if it's a directory
* return 0 if it's a file
* return -1 if it's another type of file
*/
int	is_file_or_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		perror("stat");
		return (-1);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	if (S_ISREG(path_stat.st_mode))
		return (0);
	return (-1);
}

static void	exec_cmd(char *cmd, char **args, t_shell_state *shell_state)
{
	char	**envp_args;

	if (!cmd || !*cmd || ft_strcmp(cmd, "..") == 0)
	{
		minishell_error_cmd_not_found(cmd, shell_state);
		exit(127);
	}
	envp_args = env_list_to_array(shell_state->env_vars);
	if (!execute_handler_function(args, shell_state->handlers, shell_state))
		exit(EXIT_SUCCESS);
	else if (access(cmd, F_OK) == -1)
		exec_from_path(shell_state, cmd, args, envp_args);
	else if (access(cmd, X_OK) == -1)
		minishell_error_exit_no_permission_denied(cmd, shell_state);
	else if (ft_strchr("./",*cmd) && is_file_or_directory(cmd) == 1)
		minishell_error_exit_is_directory(cmd, shell_state);
	else if (is_file_or_directory(cmd) == 0)
		execve(cmd, args, envp_args);
	minishell_error_exit_no_such_file_or_directory(cmd, shell_state);
}

static int	execute_command_from_builtins(char *cmd,
	char **args, t_shell_state *shell_state, int *status)
{
	if (cmd && *cmd)
	{
		if ((cmd) && (ft_strcmp(cmd, "exit") == 0))
			return (*status = (ft_exit(args, shell_state)), *status);
		if ((cmd) && (ft_strcmp(cmd, "cd") == 0))
			return (*status = (ft_cd(args, shell_state)), *status);
		if ((cmd) && (ft_strcmp(cmd, "export") == 0))
			return (*status = (ft_export(args, shell_state)), *status);
		if ((cmd) && (ft_strcmp(cmd, "unset") == 0))
			return (*status = (ft_unset(args, shell_state)), *status);
		if ((cmd) && (ft_strcmp(cmd, "true") == 0
				|| ft_strcmp(cmd, "false") == 0))
			return (*status = (ft_bool(args, shell_state)), *status);
	}
	return (-2);
}

static void	execute_command_parent(int *status,
	pid_t pid, t_shell_state *shell_state)
{
	g_unblock_sigquit = 0;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, status, 0);
	signal(SIGINT, SIG_DFL);
	if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		if (WTERMSIG(*status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	if (WIFEXITED(*status))
		set_exit_status(shell_state, WEXITSTATUS(*status));
	else
		set_exit_status(shell_state, -1);
}

// Fonction pour exécuter une commande
int	execute_command(char *cmd, char **args, t_shell_state *shell_state)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (!cmd)
		return (0);
	if (execute_command_from_builtins(cmd, args, shell_state, &status) != -2)
		return (status);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		sinal_handler_fork();
		exec_cmd(cmd, args, shell_state);
		perror("execvp failed");
		exit(errno);
	}
	else
		return (execute_command_parent(&status, pid, shell_state), status);
}
