/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_parse_blank.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/26 06:01:57 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_parse_blank(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	t_token	*new;
	char	*value;

	start = input;
	while (*input && (*input == ' ' || *input == '\t'))
		input++;
	shell_state->is_space = 1;
	if (shell_state->in_double_quote || shell_state->in_single_quote)
	{
		value = ft_strndup(start, input - start);
		if (value && *value != '\0')
		{
			new = new_token(TOKEN_WORD, value, shell_state);
			if (!*head)
				*head = new;
			else
				(*current)->next = new;
			*current = new;
		}
		else
			free(value);
	}
	return (input);
}

char	*handle_blank(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	return (lexer_parse_blank(head, current, input, shell_state));
}
