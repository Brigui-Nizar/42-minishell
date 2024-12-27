/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_tilde.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:18:51 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 12:02:13 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*lexer_variable(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char	*start;
	char	*end;
	t_token	*new;
	char	*var_name;

	start = input;
	end = start + 1;
	set_next_token(end, shell_state);
	var_name = ft_strdup("$HOME");
	new = new_token(TOKEN_VARIABLE, var_name, shell_state);
	if (!*head)
		*head = new;
	else
		(*current)->next = new;
	*current = new;
	return (end);
}

char	*handle_tilde(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	return (lexer_variable(head, current, input, shell_state));
}
