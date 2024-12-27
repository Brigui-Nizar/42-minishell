/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/12 11:14:03 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_flags(char **args, int *i, int *newline)
{
	int	j;

	while (args[*i] && ft_strncmp(args[*i], "-n", 2) == 0)
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
			*newline = 0;
		else
			break ;
		(*i)++;
	}
}

int	ft_echo(char **args, t_shell_state *shell_state)
{
	int	i;
	int	newline;
	int	status;

	i = 1;
	newline = 1;
	(void)shell_state;
	skip_flags(args, &i, &newline);
	while (args[i])
	{
		status = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			status = write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		status = write(STDOUT_FILENO, "\n", 1);
	if (status == -1)
	{
		perror("echo");
		exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}
