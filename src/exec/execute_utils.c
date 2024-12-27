/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 05:12:03 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_shell_state *shell_state)
{
	if (shell_state->save_stdout != -1)
		close(shell_state->save_stdout);
	if (shell_state->save_stdin != -1)
		close(shell_state->save_stdin);
	shell_state->save_stdout = -1;
	shell_state->save_stdin = -1;
}

void	save_fds(t_shell_state *shell_state)
{
	if (shell_state->save_stdout == -1)
		shell_state->save_stdout = dup(STDOUT_FILENO);
	if (shell_state->save_stdin == -1)
		shell_state->save_stdin = dup(STDIN_FILENO);
}

void	restore_fds(t_shell_state *shell_state)
{
	if (shell_state->save_stdout != -1)
	{
		close(STDOUT_FILENO);
		if (dup2(shell_state->save_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for stdout");
			exit(EXIT_FAILURE);
		}
	}
	if (shell_state->save_stdin != -1)
	{
		close(STDIN_FILENO);
		if (dup2(shell_state->save_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for stdin");
			exit(EXIT_FAILURE);
		}
	}
}

int	custom_natural_order(const char *s1, const char *s2)
{
	int				i;
	int				j;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	j = 0;
	while (s1[i] && s2[j])
	{
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[j]);
		while (c1 == '_' || c1 == '.')
			c1 = ft_tolower(s1[++i]);
		while (c2 == '_' || c2 == '.')
			c2 = ft_tolower(s2[++j]);
		if (c1 != c2)
			return (c1 - c2);
		i++;
		j++;
	}
	return (ft_tolower(s1[i]) - ft_tolower(s2[j]));
}

void	bubble_sort_natural(char **array)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (custom_natural_order(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}
