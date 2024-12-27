/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:21:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 01:47:57 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction pour créer un nouveau token
/*
** type: type du token
** value: valeur du token
** interpret: 1 si on doit interpréter les variables d'environnement, 0 sinon
** shell_state: structure de shell
*/
t_token	*new_token(t_token_type type, char *value, t_shell_state *shell_state)
{
	t_token	*token;

	(void)shell_state;
	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->is_space = shell_state->is_space;
	token->value = value;
	token->next = NULL;
	shell_state->is_space = 0;
	return (token);
}
/* 
void	add_token(t_token_type type,
	t_token **head, t_token **current, char *value, t_shell_state *shell_state)
{
	t_token	*new;

	if (value && *value != '\0')
	{
		new = new_token(type, value, shell_state);
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	else
		free(value);
} */

void	free_tokens(t_token *head)
{
	if (head != NULL)
	{
		free_tokens(head->next);
		free(head->value);
		free(head);
	}
}

static void	print_for_the_norm(t_token_type token_type,
	char *str, t_token *tmp)
{
	if (tmp->type == token_type)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" , value: ", 2);
		ft_putstr_fd(tmp->value, 2);
		ft_putstr_fd("  ,is_space ", 2);
		ft_putnbr_fd(tmp->is_space, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		print_for_the_norm(TOKEN_WORD, "TOKEN_WORD", tmp);
		print_for_the_norm(TOKEN_OPERATOR, "TOKEN_OPERATOR", tmp);
		print_for_the_norm(TOKEN_PIPE, "TOKEN_PIPE", tmp);
		print_for_the_norm(TOKEN_REDIRECT_OUTPUT, "TOKEN_REDIRECT_OUTPUT", tmp);
		print_for_the_norm(TOKEN_REDIRECT_APPEND, "TOKEN_REDIRECT_APPEND", tmp);
		print_for_the_norm(TOKEN_REDIRECT_INPUT, "TOKEN_REDIRECT_INPUT", tmp);
		print_for_the_norm(TOKEN_HEREDOC, "TOKEN_HEREDOC", tmp);
		print_for_the_norm(TOKEN_PAREN_OPEN, "TOKEN_PAREN_OPEN", tmp);
		print_for_the_norm(TOKEN_PAREN_CLOSE, "TOKEN_PAREN_CLOSE", tmp);
		print_for_the_norm(TOKEN_END, "TOKEN_END", tmp);
		print_for_the_norm(TOKEN_SUBSHELL, "TOKEN_SUBSHELL", tmp);
		print_for_the_norm(TOKEN_VARIABLE, "TOKEN_VARIABLE", tmp);
		print_for_the_norm(TOKEN_ASSIGNMENT, "TOKEN_ASSIGNMENT", tmp);
		print_for_the_norm(TOKEN_DOUBLE_QUOTE, "TOKEN_DOUBLE_QUOTE", tmp);
		print_for_the_norm(TOKEN_SINGLE_QUOTE, "TOKEN_SINGLE_QUOTE", tmp);
		print_for_the_norm(TOKEN_WILDCARD, "TOKEN_WILDCARD", tmp);
		tmp = tmp->next;
	}
}
