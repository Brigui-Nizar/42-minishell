/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 05:10:28 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_in_parenthesis(char c, t_shell_state *shell_state)
{
	if (ft_strchr("(", c) != NULL
		&& !shell_state->in_single_quote && !shell_state->in_parent)
		return (1);
	if (ft_strchr(")", c) != NULL
		&& !shell_state->in_single_quote && shell_state->in_parent)
		return (1);
	return (0);
}

static int	norm_is_end_of_word(char c, t_shell_state *shell_state)
{
	if (c == '\t' && !shell_state->in_single_quote
		&& !shell_state->in_double_quote && !shell_state->in_parent)
		return (1);
	if (ft_strchr("=", c) != NULL
		&& !shell_state->in_single_quote && !shell_state->in_parent
		&& !shell_state->in_assignement)
		return (1);
	if (ft_strchr("$", c) != NULL
		&& !shell_state->in_single_quote && !shell_state->in_parent)
		return (shell_state->in_assignement = 0, 1);
	if (ft_strchr("&|><\\", c) != NULL
		&& !shell_state->in_single_quote && !shell_state->in_parent
		&& !shell_state->in_double_quote)
		return (shell_state->in_assignement = 0, 1);
	if (handle_in_parenthesis(c, shell_state))
		return (1);
	if (c == ' ' && !shell_state->in_single_quote
		&& !shell_state->in_double_quote && !shell_state->in_parent)
	{
		shell_state->in_assignement = 0;
		shell_state->is_space = 1;
		return (1);
	}
	return (0);
}

static int	is_end_of_word(char c, t_shell_state *shell_state)
{
	if (c == '\'' && !shell_state->in_double_quote && !shell_state->in_parent)
	{
		shell_state->in_single_quote = !shell_state->in_single_quote;
		return (1);
	}
	if (c == '\"' && !shell_state->in_single_quote && !shell_state->in_parent)
		return (1);
	if (norm_is_end_of_word(c, shell_state))
		return (1);
	return (0);
}

/* Un mot (commande ou argument)
// Exemple: "ls -l | grep foo && echo bar"
// Retourne un token de type TOKEN_WORD avec la valeur "ls"
// et avance l'index de l'entrée à "-l | grep foo && echo bar"
*/
static char	*lexer_word(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*value;
	t_token	*new;

	start = input;
	while (*input && !is_end_of_word(*input, shell_state))
		input++;
	if (*input == '&' && *(input + 1) != '&')
	{
		input++;
	}
	value = ft_strndup(start, input - start);
	set_next_token(input, shell_state);
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
	return (input);
}

char	*handle_word(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	return (lexer_word(head, current, input, shell_state));
}
