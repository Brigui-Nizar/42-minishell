/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 04:44:45 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*args_to_string(char **args)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (args[i])
	{
		str = ft_strjoin_free(str, args[i]);
		if (args[i + 1])
			str = ft_strjoin_free(str, " ");
		i++;
	}
	return (str);
}

static char	**args_for_subshell(t_ast_node *subshell_node,
	t_shell_state *shell_state, char *minishell)
{
	char	**args;

	(void)shell_state;
	args = ft_calloc(4, sizeof(char *));
	if (!args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	args[0] = minishell;
	args[1] = ft_strdup("-c");
	args[2] = ft_strdup(subshell_node->left->value);
	args[3] = NULL;
	return (args);
}

static void	handle_subshell_fork(t_ast_node *subshell_node,
	t_shell_state *shell_state)
{
	char	*minishell;
	char	**args;
	char	**envp_args;

	signal(SIGINT, SIG_IGN);
	minishell = ft_strjoin(shell_state->minishell_path, "/minishell");
	args = args_for_subshell(subshell_node, shell_state, minishell);
	envp_args = env_list_to_array(shell_state->env_vars);
	execve(minishell, args, envp_args);
	perror("execve failed in subshell");
	exit(1);
}

static void	execute_subshell_exit_status(t_shell_state *shell_state, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) != 0)
		set_exit_status(shell_state, WTERMSIG(status));
	else if (WIFEXITED(status))
		set_exit_status(shell_state, WEXITSTATUS(status));
	else
		set_exit_status(shell_state, -1);
}

void	execute_subshell(t_ast_node *subshell_node, t_shell_state *shell_state)
{
	int		status;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		handle_subshell_fork(subshell_node, shell_state);
	close(pipefd[0]);
	close(pipefd[1]);
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		execute_subshell_exit_status(shell_state, status);
	}
	else
		perror("fork failed");
}
