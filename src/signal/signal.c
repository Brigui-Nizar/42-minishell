/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:44:35 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 13:51:03 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_unblock_sigquit = 0;

/*
	gestion des signaux
*/
static void	handle_sigint_main(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_unblock_sigquit = signum;
}

/*
	gestion des signaux
*/
void	sinal_handler_main(void)
{
	signal(SIGINT, handle_sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_main_print_message(void)
{
	if (g_unblock_sigquit == SIGKILL)
		ft_putstr_fd("Killed: 9\n", 2);
	else if (g_unblock_sigquit == SIGTERM)
		ft_putstr_fd("Terminated: 15\n", 2);
	else if (g_unblock_sigquit == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	main_signal_set_exit_status(t_shell_state *shell_state)
{
	if (g_unblock_sigquit != 0)
	{
		set_exit_status(shell_state, g_unblock_sigquit + 128);
		g_unblock_sigquit = 0;
	}
}
/* static void	handle_sigint_fork(int signum)
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
} */
