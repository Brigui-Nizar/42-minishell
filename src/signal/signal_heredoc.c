/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:51:23 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:58:30 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint_herdoc(int signum)
{
	int	**pipefd;

	pipefd = ppipe();
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close((*pipefd)[0]);
		close((*pipefd)[1]);
		exit(130);
	}
}

void	sinal_handler_heredoc(void)
{
	signal(SIGINT, handle_sigint_herdoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handle_heredoc_sigint(int signum)
{
	printf("\n");
	g_unblock_sigquit = signum;
}
