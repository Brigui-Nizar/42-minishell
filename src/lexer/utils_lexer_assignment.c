/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_assignment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 13:45:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_assignment(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	t_token	*new;

	set_next_token(input + 1, shell_state);
	new = new_token(TOKEN_ASSIGNMENT, ft_strndup(input, 1), shell_state);
	input++;
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (input);
}

char	*handle_assignment(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	(void)shell_state;
	shell_state->in_assignement = !shell_state->in_assignement;
	return (lexer_assignment(head, current, input, shell_state));
}
