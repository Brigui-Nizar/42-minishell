/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_unexpected.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:06:27 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 14:38:48 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 
	bash: syntax error near
	unexpected token `>>'
	a gerer "| cmd"
	"-"
	"''"
	.
	..
	~
	4test=test1

*/
int	handle_check_input_final(t_unexpected *c);

int	check_redirection(char *line, int *n, \
int in_single_quote, int in_double_quote);

static int	check_input_quotes(char *line, t_unexpected *c)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (line[i])
	{
		update_quotes_state(line[i], &in_single_quote, &in_double_quote, &i);
		if (!in_double_quote && !in_single_quote
			&& handle_no_quotes(line, &i, c))
			return (line[i]);
		else if (!in_double_quote && in_single_quote
			&& handle_quotes(line, &i, '\'', c))
			return (line[i]);
		else if (in_double_quote && !in_single_quote
			&& handle_quotes(line, &i, '"', c))
			return (line[i]);
	}
	return (-1);
}

/*
** check if the input has an unexpected token
** return the unexpected token if found
** check redirections
** cherck subshell
*/
int	check_redirection(char *line,
	int *n, int in_single_quote, int in_double_quote)
{
	int		i;
	int		j;
	char	tmp;

	i = *n;
	if (in_single_quote)
		return (0);
	if ((line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '<' && line[i + 1] == '<'))
		return (0);
	if (line[i] == '>' || line[i] == '<' || line[i] == '(' || line[i] == ')')
	{
		tmp = line[i];
		j = i + 1;
		while (line[j] == ' ' || line[j] == '\t')
		{
			if (in_double_quote && line[j] == '"')
				break ;
			j++;
		}
		if (((tmp == '>' || tmp == '<') && (line[j] == '>' || line[j] == '<'))
			|| (tmp == '(' && line[j] == ')') || (tmp == ')' && line[j] == '('))
			return (1);
	}
	return (0);
}

char	is_unexpected_token(const char *line)
{
	t_unexpected	*c;

	if (ft_strlen(line) == 1 && ft_strchr("<|&", line[0]) != NULL)
		return (line[0]);
	if (ft_strlen(line) == 2 && (ft_strcmp(">>", line) == 0
			|| ft_strcmp("&&", line) == 0 || ft_strcmp("||", line) == 0))
		return (line[0]);
	c = ft_calloc(1, sizeof(t_unexpected));
	if (check_input_quotes((char *) line, c) != -1)
		return (1);
	if (handle_check_input_final(c))
	{
		free(c);
		return (1);
	}
	free(c);
	return (0);
}

static int	is_unexpected_exlamation(t_shell_state *shell_state)
{
	if (ft_strlen(shell_state->input) == 1
		&& ft_strchr("!", *shell_state->input) != NULL)
	{
		update_set(shell_state, "?", "1");
		return (1);
	}
	return (0);
}

int	is_unexpected_input(t_shell_state *shell_state)
{
	if (is_unexpected_exlamation(shell_state))
	{
		if (shell_state->input)
			free(shell_state->input);
		shell_state->input = NULL;
		return (1);
	}
	if (shell_state->input != NULL && ft_strlen(shell_state->input) == 0)
		return (0);
	if (shell_state->input && (ft_strchr("|", *shell_state->input) != NULL
			|| is_unexpected_token(shell_state->input) != 0
			|| !are_quotes_closed(shell_state->input)))
	{
		minishell_error_unexpected_token(shell_state);
		if (shell_state->input)
			free(shell_state->input);
		shell_state->input = NULL;
		return (1);
	}
	return (0);
}
