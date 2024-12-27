/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 13:19:32 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
t_ast_node	set_lst_last(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return (*new);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp = new;
	*lst = tmp;
	return (*tmp);
} */

t_ast_node	*parse_quoted_content(t_token **tokens)
{
	t_token		*current;
	t_ast_node	*content_node;
	t_ast_node	*new_node;

	current = *tokens;
	content_node = NULL;
	while (current && current->type != TOKEN_DOUBLE_QUOTE
		&& current->type != TOKEN_SINGLE_QUOTE)
	{
		new_node = new_ast_node(current->type,
				current->value, current->is_space);
		lst_add_back(&content_node, new_node);
		current = current->next;
	}
	if (current && (current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE))
	{
		new_node = new_ast_node(current->type,
				current->value, current->is_space);
		lst_add_back(&content_node, new_node);
	}
	current = current->next;
	*tokens = current;
	return (content_node);
}

int	handle_token_assigment_no_key(t_token **tokens,
	t_token *current, t_ast_node **command_node)
{
	t_ast_node	*assignment_node;

	if (current && current->type == TOKEN_ASSIGNMENT)
	{
		assignment_node = new_ast_node(current->type,
				current->value, current->is_space);
		assignment_node->left = new_ast_node(TOKEN_WORD,
				"", 1);
		current = current->next;
		if (assignment_node->is_space == 0)
			handle_assignement_double_quote(&current, &assignment_node);
		else
			assignment_node->right = new_ast_node(TOKEN_WORD,
					"", 1);
		*tokens = current;
		lst_add_back(command_node, assignment_node);
		return (1);
	}
	return (0);
}

int	handle_token_assigment_key(t_token **tokens,
	t_token *current, t_ast_node **command_node)
{
	t_ast_node	*assignment_node;

	if (current->next && current->next->type == TOKEN_ASSIGNMENT
		&& current->is_space == 0)
	{
		assignment_node = new_ast_node(current->next->type,
				current->next->value, current->next->is_space);
		assignment_node->left = new_ast_node(current->type,
				current->value, current->is_space);
		if (assignment_node->is_space == 1)
		{
			assignment_node->right = new_ast_node(TOKEN_WORD,
					"", 1);
			current = current->next->next;
		}
		else
		{
			current = current->next->next;
			handle_assignement_double_quote(&current, &assignment_node);
		}
		*tokens = current;
		lst_add_back(command_node, assignment_node);
		return (1);
	}
	return (0);
}

/*
** Function to handle base token
*/
static int	handle_base_token(t_token **tokens, t_ast_node **command_node)
{
	t_token		*current;
	t_ast_node	*new_node;

	current = *tokens;
	if (handle_token_assigment_key(tokens, current, command_node))
		return (1);
	else if (handle_token_assigment_no_key(tokens, current, command_node))
		return (1);
	new_node = new_ast_node(current->type,
			current->value, current->is_space);
	lst_add_back(command_node, new_node);
	*tokens = current->next;
	return (0);
}

/*
	Function to parse a command and return an ast node
*/
t_ast_node	*parse_command(t_token **tokens)
{
	t_token		*current;
	t_ast_node	*command_node;

	current = *tokens;
	command_node = NULL;
	while (current && (current->type == TOKEN_WORD
			|| current->type == TOKEN_VARIABLE
			|| current->type == TOKEN_ASSIGNMENT
			|| current->type == TOKEN_DOUBLE_QUOTE
			|| current->type == TOKEN_SINGLE_QUOTE
			|| current->type == TOKEN_WILDCARD))
	{
		if (handle_base_token(&current, &command_node))
			continue ;
	}
	return (command_node);
}
