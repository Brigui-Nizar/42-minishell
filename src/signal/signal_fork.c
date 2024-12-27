/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:31:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 05:40:02 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint_fork(int signum)
{
	if (signum == SIGINT)
	{
		g_unblock_sigquit = 1;
		write(STDIN_FILENO, "\n", 1);
		exit(130);
	}
}

static void	handle_sigquit_fork(int signum)
{
	if (signum == SIGQUIT)
	{
		g_unblock_sigquit = 1;
		ft_putstr_fd("Quit (core dumped)", 2);
		write(STDIN_FILENO, "\n", 1);
		exit(131);
	}
}

void	sinal_handler_fork(void)
{
	signal(SIGINT, handle_sigint_fork);
	signal(SIGQUIT, handle_sigquit_fork);
}
/* 
static void	new_handle_sigint(int signum)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_unblock_sigquit = signum;
}

static void	handle_sigquit_fork(int signum)
{
	if (signum == SIGQUIT)
	{
		g_unblock_sigquit = SIGQUIT;
		exit(131);
	}
}

void	signal_fork(void)
{
	signal(SIGINT, new_handle_sigint);
	signal(SIGQUIT, handle_sigquit_fork);
}
 */