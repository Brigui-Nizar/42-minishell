/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 01:40:41 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_pipe(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	new = new_token(TOKEN_PIPE, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

char	*handle_pipe(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	shell_state->is_space = 1;
	return (lexer_pipe(head, current, input, shell_state));
}
