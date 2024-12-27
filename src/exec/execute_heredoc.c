/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:40:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 13:04:52 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(int nb, ...);

static void	norm_heredoc(int pipefd[2], const char *delimiter)
{
	char	*line;
	char	*str;

	sinal_handler_heredoc();
	str = ft_strdup("");
	line = NULL;
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			handle_heredoc_error(delimiter);
			break ;
		}
		if ((ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
			&& ft_strlen(line) - 1 == ft_strlen(delimiter))
			break ;
		str = ft_strjoin_free_s1_s2(str, line);
	}
	write(pipefd[1], str, ft_strlen(str));
	free_all(2, str, line);
	close(pipefd[1]);
}

void	close_fds(t_shell_state *shell_state);

void	read_heredoc_input(t_shell_state *shell_state,
	int pipefd[2], const char *delimiter)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("fork failed\n", 2);
		return ;
	}
	if (pid == 0)
	{
		close_fds(shell_state);
		close(pipefd[0]);
		norm_heredoc(pipefd, delimiter);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		set_exit_status(shell_state, WEXITSTATUS(status));
		g_unblock_sigquit = 0;
		return ;
	}
}

void	heredoc_input(t_shell_state *shell_state, const char *delimiter)
{
	int	pipefd[2];

	signal(SIGINT, SIG_IGN);
	restore_fds(shell_state);
	if (init_pipe(pipefd) == -1)
		return ;
	read_heredoc_input(shell_state, pipefd, delimiter);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_putstr_fd("dup2 failed\n", 2);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	norm_heredoc_input(t_ast_node *root,
	t_shell_state *shell_state)
{
	heredoc_input(shell_state, root->right->value);
	if (root->right && root->right->right)
		execute_ast(root->right->right, shell_state);
}
/* void handle_sigint_heredoc(int signum)
{
    (void)signum;
    rl_replace_line("", 0); // Effacer la ligne en cours
    rl_done = 0; // Quitter la boucle readline
	rl_eof_found = 1;
    write(STDOUT_FILENO, "\n", 1); // Afficher une nouvelle ligne
} */
