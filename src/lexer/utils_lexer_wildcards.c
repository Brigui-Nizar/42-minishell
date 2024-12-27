/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_wildcards.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/26 01:03:13 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_wildcard(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*end;
	t_token	*new;
	char	*var_name;

	start = input;
	end = start + 1;
	while (*end && !strchr(" *'\"=\t&|><()", *end))
		end++;
	var_name = ft_strndup(start, end - start);
	new = new_token(TOKEN_WILDCARD, var_name, shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (end);
}

char	*handle_wildcard(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	if (*input == '*')
		return (lexer_wildcard(head, current, input, shell_state));
	return (input);
}
