/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_double_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/29 05:16:27 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_double_quote(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	if (*input && (*(input + 1) != ' ' && *(input + 1) != '\t'))
		shell_state->is_space = 0;
	else
		shell_state->is_space = 1;
	new = new_token(TOKEN_DOUBLE_QUOTE, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

char	*handle_double_quote(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	shell_state->in_double_quote = !shell_state->in_double_quote;
	return (lexer_double_quote(head, current, input, shell_state));
}
