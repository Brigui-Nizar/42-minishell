/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 01:37:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_end(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	shell_state->is_space = 1;
	new = new_token(TOKEN_END, ft_strndup(input, 1), shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

char	*handle_end(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	return (lexer_end(head, current, input, shell_state));
}
