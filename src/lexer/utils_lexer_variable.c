/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 13:45:41 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_next_token(char *end, t_shell_state *shell_state)
{
	if (*(end) != '\0' && *(end) == ' ')
	{
		shell_state->is_space = 1;
	}
	else
	{
		shell_state->is_space = 0;
	}
}

static void	handle_lexer_variable_set_end(char *start,
	char **var_name, char **end)
{
	if (*(start + 1) == '?')
	{
		*var_name = ft_strdup("$?");
		*end = start + 2;
	}
	else if (*(start + 1) == '*')
	{
		*var_name = ft_strdup("$*");
		*end = start + 2;
	}
	else if (*(start + 1) == '=')
	{
		*var_name = ft_strdup("$=");
		*end = start + 2;
	}
	else
	{
		*end = start + 1;
		if (ft_isdigit(**end))
			(*end)++;
		else
			while (**end && (ft_isalnum(**end) || **end == '_'))
				(*end)++;
		*var_name = ft_strndup(start, *end - start);
	}
}

static char	*lexer_variable(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*end;
	t_token	*new;
	char	*var_name;

	start = input;
	handle_lexer_variable_set_end(start, &var_name, &end);
	set_next_token(end, shell_state);
	if (var_name && var_name[1] == '=')
	{
		new = new_token(TOKEN_WORD, var_name, shell_state);
	}
	else
		new = new_token(TOKEN_VARIABLE, var_name, shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (end);
}

char	*handle_variable(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	return (lexer_variable(head, current, input, shell_state));
}
