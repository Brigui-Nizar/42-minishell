/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 01:39:10 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** Gère >> ou >
*/
static char	*lexer_redirection_ouput(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	if (*input == '>' && *(input + 1) == '>')
	{
		new = new_token(TOKEN_REDIRECT_APPEND,
				ft_strndup(input, 2), shell_state);
		input += 2;
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	else
	{
		new = new_token(TOKEN_REDIRECT_OUTPUT,
				strndup(input, 1), shell_state);
		input++;
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	return (input);
}

static char	*lexer_redirection_input(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	shell_state->is_space = 1;
	if (*input == '<' && *(input + 1) == '<')
	{
		new = new_token(TOKEN_HEREDOC, ft_strndup(input, 2), shell_state);
		input += 2;
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	else
	{
		new = new_token(TOKEN_REDIRECT_INPUT, strndup(input, 1), shell_state);
		input++;
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	return (input);
}

static char	*lexer_redirection(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	if (*input == '>')
		return (lexer_redirection_ouput(head, current, input, shell_state));
	else
		return (lexer_redirection_input(head, current, input, shell_state));
}

char	*handle_redirection(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	return (lexer_redirection(head, current, input, shell_state));
}
