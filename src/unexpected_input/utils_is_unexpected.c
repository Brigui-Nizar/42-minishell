/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_unexpected.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 08:06:27 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 11:35:38 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	reset_unexpected(t_unexpected *c)
{
	c->pipe = 0;
	c->sup = 0;
	c->inf = 0;
	c->and = 0;
	c->semicolon = 0;
	c->parent_open = 0;
	c->parent_close = 0;
}

int	handle_check_input(t_unexpected *c);

static void	update_token_counts(t_unexpected *c, char token)
{
	if (ft_isalnum(token) || ft_strchr("_", token))
		reset_unexpected(c);
	if (token == '|')
		c->pipe++;
	if (token == '>')
		c->sup++;
	if (token == '<')
		c->inf++;
	if (token == '&')
		c->and++;
	if (token == ';')
		c->semicolon++;
	if (token == '(')
		c->parent_open++;
	if (token == ')')
		c->parent_close++;
	if (token == '(')
		c->parent++;
	if (token == ')')
		c->parent--;
}

void	update_quotes_state(char c,
	int *in_single_quote, int *in_double_quote, int *i)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*i)++;
	}
	else if (c == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		(*i)++;
	}
}

char	handle_quotes(const char *line, int *i, char quote, t_unexpected *c)
{
	reset_unexpected(c);
	while (line[*i] && line[*i] != quote)
	{
		update_token_counts(c, line[*i]);
		if (handle_check_input(c))
			return (free(c), line[*i]);
		(*i)++;
	}
	return (0);
}

int	check_redirection(char *line, \
int *n, int in_single_quote, int in_double_quote);

char	handle_no_quotes(const char *line, int *i, t_unexpected *c)
{
	reset_unexpected(c);
	while (line[*i] && line[*i] != '"' && line[*i] != '\'')
	{
		if (check_redirection((char *) line, i, 0, 0))
			return (free(c), line[*i]);
		update_token_counts(c, line[*i]);
		if (handle_check_input(c))
			return (free(c), line[*i]);
		(*i)++;
	}
	return (0);
}
