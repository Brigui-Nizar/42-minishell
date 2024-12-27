/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_single_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/30 00:24:17 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_single_quote_head(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_SINGLE_QUOTE, ft_strdup("\'"), shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input + 1);
}

static char	*lexer_single_quote_tail(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	set_next_token(input + 1, shell_state);
	new = new_token(TOKEN_SINGLE_QUOTE, ft_strdup("\'"), shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input + 1);
}

static char	*lexer_single_quote_word(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*end;
	t_token	*new;
	char	*var_name;

	start = input;
	end = start;
	while (*end && *end != '\'')
		end++;
	var_name = ft_strndup(start, end - start);
	if (ft_strlen(var_name) == 0)
	{
		free(var_name);
		return (end);
	}
	else
	{
		set_next_token(end, shell_state);
		new = new_token(TOKEN_WORD, var_name, shell_state);
	}
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	return (*current = new, end);
}

char	*handle_single_quote(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	input = lexer_single_quote_head(head, current, input, shell_state);
	input = lexer_single_quote_word(head, current, input, shell_state);
	input = lexer_single_quote_tail(head, current, input, shell_state);
	shell_state->in_single_quote = !shell_state->in_single_quote;
	return (input);
}
