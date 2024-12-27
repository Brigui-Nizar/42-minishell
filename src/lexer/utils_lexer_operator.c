/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:35:41 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_operator_or(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_OR, ft_strndup(input, 2), shell_state);
	input += 2;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

static char	*lexer_operator_and(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_AND, ft_strndup(input, 2), shell_state);
	input += 2;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

static char	*lexer_operator(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	shell_state->is_space = 1;
	if (ft_strncmp(input, "||", 2) == 0)
		return (lexer_operator_or(head, current, input, shell_state));
	else
		return (lexer_operator_and(head, current, input, shell_state));
}

char	*handle_operator(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	return (lexer_operator(head, current, input, shell_state));
}
