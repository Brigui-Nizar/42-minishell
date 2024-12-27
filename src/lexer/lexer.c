/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:48:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_backslash(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	input++;
	set_next_token(input + 1, shell_state);
	new = new_token(TOKEN_WORD, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

char	*handle_backslash(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	return (lexer_backslash(head, current, input, shell_state));
}

static char	*handle_input(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	if (!shell_state->in_single_quote && (*input == ' ' || *input == '\t'))
		return (handle_blank(head, current, input, shell_state));
	if (*input == '\\')
		return (handle_backslash(head, current, input, shell_state));
	else if (*input == '~' && !shell_state->in_single_quote)
		return (handle_tilde(head, current, input, shell_state));
	else if (*input == '$' && !shell_state->in_single_quote)
		return (handle_variable(head, current, input, shell_state));
	else if (*input == '"' && !shell_state->in_single_quote)
		return (handle_double_quote(head, current, input, shell_state));
	else if (*input == '\''
		&& !shell_state->in_double_quote && shell_state->in_single_quote)
		return (handle_single_quote(head, current, input, shell_state));
	else if (*input == '=' && !shell_state->in_assignement)
		return (handle_assignment(head, current, input, shell_state));
	else if (ft_strncmp(input, "||", 2) == 0 || ft_strncmp(input, "&&", 2) == 0)
		return (handle_operator(head, current, input, shell_state));
	else if (*input == '|' && !shell_state->in_double_quote)
		return (handle_pipe(head, current, input, shell_state));
	else if ((*input == '>' || *input == '<') && !shell_state->in_double_quote)
		return (handle_redirection(head, current, input, shell_state));
	else if (*input == '(' || *input == ')')
		return (handle_parenthesis(head, current, input, shell_state));
	else
		return (input);
}

t_token	*lexer(char *input, t_shell_state *shell_state)
{
	t_token	*head;
	t_token	*current;

	head = NULL;
	current = NULL;
	shell_state->in_double_quote = 0;
	shell_state->in_single_quote = 0;
	shell_state->in_assignement = 0;
	shell_state->in_parent = 0;
	shell_state->is_space = 0;
	while (*input)
	{
		input = handle_input(&head, &current, input, shell_state);
		input = handle_word(&head, &current, input, shell_state);
	}
	input = handle_end(&head, &current, input, shell_state);
	shell_state->tokens = head;
	shell_state->tokens_tmp = head;
	return (head);
}
