/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/04 05:50:54 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_parent_open(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_PAREN_OPEN, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

static char	*lexer_parent_close(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_PAREN_CLOSE, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

void	loop_lexer_parent_word(char **end)
{
	int		count_parent_open;
	int		count_parent_close;

	count_parent_open = 1;
	count_parent_close = 0;
	while (end && **end != '\'')
	{
		if (**end == '(')
			count_parent_open++;
		if (**end == ')')
			count_parent_close++;
		if (count_parent_open == count_parent_close)
			break ;
		(*end)++;
	}
}

static char	*lexer_parent_word(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*end;
	t_token	*new;
	char	*var_name;

	start = input;
	end = start;
	loop_lexer_parent_word(&end);
	var_name = ft_strndup(start, end - start);
	set_next_token(end + 1, shell_state);
	new = new_token(TOKEN_WORD, var_name, shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	return (*current = new, end);
}
/* 
char	*lexer_parent(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	shell_state->is_space = 1;
	input = lexer_parent_open(head, current, input, shell_state);
	input = lexer_parent_word(head, current, input, shell_state);
	input = lexer_parent_close(head, current, input, shell_state);
	return (input);
} */

char	*handle_parenthesis(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	shell_state->is_space = 1;
	input = lexer_parent_open(head, current, input, shell_state);
	input = lexer_parent_word(head, current, input, shell_state);
	input = lexer_parent_close(head, current, input, shell_state);
	return (input);
}
