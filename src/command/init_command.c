/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:16:05 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/24 03:57:43 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*handler_get_full_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;
	char	*tmp_path;

	temp = ft_strjoin(dir, "/");
	if (*command == '.' && *command + 1 == '/')
	{
		free(temp);
		tmp_path = getcwd(NULL, 0);
		temp = ft_strjoin_free(tmp_path, "/");
		full_path = ft_strjoin_free(temp, command + 2);
	}
	else
		full_path = ft_strjoin_free(temp, command);
	return (full_path);
}

static int	handle_check_path(char **dir,
	char **argv, char **envp, char *command)
{
	char		*full_path;
	int			i;
	int			found;

	found = 0;
	i = 0;
	while (dir[i] != NULL && !found)
	{
		full_path = handler_get_full_path(dir[i], command);
		if (access(full_path, X_OK) == 0)
		{
			found = 1;
			execve(full_path, argv, envp);
			perror("execve from path");
			free(full_path);
			free_split(dir);
			exit(EXIT_FAILURE);
		}
		i++;
		free(full_path);
	}
	free_split(dir);
	return (found);
}

/*
	FUNCTION: exec_from_path
	DESCRIPTION:
		Execute a command from the PATH environment variable
*/
void	exec_from_path(t_shell_state *shell_state, char *command,
	char **argv, char **envp)
{
	t_env_var	*getsetvalue;
	char		*path;
	char		**dir;
	int			found;

	getsetvalue = find_env_var(shell_state->env_vars, "PATH");
	if (getsetvalue == NULL)
		return ;
	path = getsetvalue->value;
	rl_clear_history();
	if (path == NULL)
		minishell_error_exit_no_path();
	dir = ft_split(path, ':');
	found = handle_check_path(dir, argv, envp, command);
	if (found)
		exit(EXIT_SUCCESS);
	minishell_error_cmd_not_found(command, shell_state);
	exit(127);
}
/* int static handler_is_accessible(char *full_path)
{
	if (access(full_path, F_OK) == 0)
		return (1);
	return (0);
} */
/*
else if (access(cmd, F_OK) == -1)
	{
		exec_from_path(shell_state, cmd, args, envp_args);
	}
	else if (access(cmd, X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd);
		exit(EXIT_FAILURE);
	}
*/