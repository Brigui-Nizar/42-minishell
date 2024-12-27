/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:41:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/12 23:38:39 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_shell(t_shell_state *shell_state, int status_code)
{
	free(shell_state->prompt);
	free(shell_state->minishell_path);
	ft_lst_builtins_clear(&shell_state->handlers, free);
	lst_clear_env(shell_state->env_vars);
	rl_clear_history();
	free_minishell_loop(shell_state);
	exit(status_code);
}

int	is_valid_input(char *input, t_shell_state *shell_state)
{
	int		len;

	if (!input)
	{
		printf("exit\n");
		exit_shell(shell_state, EXIT_SUCCESS);
	}
	len = ft_strlen(input);
	if (len == 0)
		return (0);
	if (input[0] == '\n')
		return (0);
	if (len == 1 && ft_strchr("\t:", input[0]) != NULL)
	{
		return (0);
	}
	while (*input && ft_isascii(*input))
		input++;
	len = ft_strlen(input);
	if (len != 0 || !ft_isascii(*input))
	{
		printf("UTF-8 character\n");
		return (0);
	}
	return (1);
}

int	are_quotes_closed(const char *line)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (line[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (!in_single_quote && !in_double_quote);
}
/* char	is_unexpected_token(const char *line)
{
	int	in_single_quote;
	int	in_double_quote;
	int	i;
	t_unexpected *c;

	c = ft_calloc(1, sizeof(t_unexpected));
	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (line[i])
	{
		if (!line[i])
			break;
		update_quotes_state(line[i], &in_single_quote, &in_double_quote, &i);
		if (!in_double_quote && !in_single_quote)
		{
			ft_memset(c, 0, sizeof(t_unexpected));
			while(line[i] && line[i] != '"' && line[i] != '\'')
			{
				update_token_counts(c, line[i]);			
				if (handle_check_input(c))
					return (free(c),line[i]);
				i++;
			}
			continue;
		}
		if (!in_double_quote && in_single_quote)
		{
			ft_memset(c, 0, sizeof(t_unexpected));
			while(line[i] && line[i] != '\'')
			{
				update_token_counts(c, line[i]);
				if (handle_check_input(c))
					return (free(c),line[i]);
				i++;
			}
			continue;
		}
		if (in_double_quote && !in_single_quote)
		{
			ft_memset(c, 0, sizeof(t_unexpected));
			while(line[i] && line[i] != '"')
			{
				update_token_counts(c, line[i]);
				if (handle_check_input(c))
					return (free(c),line[i]);
				i++;
			}
			continue;
		}
	}
	free(c);
	return (0);
} */

char	*get_complete_input(char *initial_input)
{
	char	*line;
	char	*complete_input;

	if (!initial_input)
		return (initial_input);
	complete_input = ft_strdup(initial_input);
	while (!are_quotes_closed(complete_input))
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		complete_input = ft_strjoin_free(complete_input, line);
		free(line);
	}
	free(initial_input);
	return (complete_input);
}
