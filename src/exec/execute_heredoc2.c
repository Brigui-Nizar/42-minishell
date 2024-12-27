/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:34:21 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:41:18 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc_error(const char *delimiter)
{
	ft_putstr_fd("avertissement : « here-document » délimité par ", 2);
	ft_putstr_fd("la fin du fichier (au lieu de « ", 2);
	ft_putstr_fd((char *)delimiter, 2);
	ft_putstr_fd(" »)\n", 2);
}

int	**ppipe(void)
{
	static int	*pipefd[2];

	return (pipefd);
}

int	init_pipe(int pipefd[2])
{
	int	**pipefd2;

	pipefd2 = ppipe();
	if (pipe(pipefd) == -1)
	{
		ft_putstr_fd("pipe failed\n", 2);
		return (-1);
	}
	*pipefd2 = pipefd;
	return (0);
}
