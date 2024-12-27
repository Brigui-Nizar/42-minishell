/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 04:26:30 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_shell_state *shell_state);

static void	execute_pipe1(int pipefd[2],
	t_ast_node *left, t_shell_state *shell_state)
{
	int	status;
	int	status_signal;

	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	rl_clear_history();
	status = execute_ast(left, shell_state);
	close_fds(shell_state);
	if (WIFSIGNALED(status))
	{
		status_signal = WTERMSIG(status) & 0x7F;
		status_signal |= 0x80;
		exit (status_signal);
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(-1);
}

static void	execute_pipe2(int pipefd[2],
	t_ast_node *right, t_shell_state *shell_state)
{
	int	status;
	int	status_signal;

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	rl_clear_history();
	status = execute_ast(right, shell_state);
	close_fds(shell_state);
	if (WIFSIGNALED(status))
	{
		status_signal = WTERMSIG(status) & 0x7F;
		status_signal |= 0x80;
		exit (status_signal);
	}
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(EXIT_FAILURE);
}

static int	create_pipe(int (*pipefd)[2], t_shell_state *shell_state)
{
	int	is_pipe;

	is_pipe = pipe(*pipefd);
	if (is_pipe == -1)
	{
		minishell_error_pipe(shell_state);
		return (0);
	}
	return (1);
}

static int	wait_for_child(pid_t pid1, pid_t pid2,
	t_shell_state *shell_state)
{
	pid_t	wait_pid;
	int		i;
	int		status;
	int		status1;
	int		status2;

	i = 0;
	while (i < 2)
	{
		wait_pid = wait(&status);
		if (wait_pid == pid1)
			status1 = WEXITSTATUS(status);
		if (wait_pid == pid2)
			status2 = WEXITSTATUS(status);
		i++;
	}
	status = (status2);
	if (status2 != 0 && status2 != 1)
		status = status1;
	set_exit_status(shell_state, status);
	return (status);
}

int	execute_pipe(t_ast_node *left,
	t_ast_node *right, t_shell_state *shell_state)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	if (!create_pipe(&pipefd, shell_state))
		return (-1);
	pid1 = fork();
	if (pid1 == 0)
		execute_pipe1(pipefd, left, shell_state);
	pid2 = fork();
	if (pid2 == 0)
		execute_pipe2(pipefd, right, shell_state);
	close(pipefd[0]);
	close(pipefd[1]);
	if (pid1 > 0 && pid2 > 0)
		return (wait_for_child(pid1, pid2, shell_state));
	exit(0);
}
