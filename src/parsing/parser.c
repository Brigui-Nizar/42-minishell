/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/16 18:36:15 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Fonction simple pour parser les tokens en un AST (exemple très basique)
// Parsing (Analyse Syntaxique)
// Exemple: "ls -l | grep foo && echo bar"
/*
AST:
- OPERATOR "&&"
  - PIPE "|"
	- WORD "ls"
	  - WORD "-l"
	- WORD "grep"
	  - WORD "foo"
  - WORD "echo"
	- WORD "bar"
*/
// Retourne un nœud de l'AST
//
static void	handle_subshell(t_token **token,
	t_ast_node **left_node, int min_precedence)
{
	t_token		*current;
	t_ast_node	*sub_expr;
	t_ast_node	*paren_node;

	current = *token;
	(void)min_precedence;
	if (current->type == TOKEN_PAREN_OPEN)
	{
		current = current->next;
		sub_expr = new_ast_node(TOKEN_WORD, current->value, current->is_space);
		current = current->next;
		if (current->type == TOKEN_PAREN_CLOSE)
			current = current->next;
		paren_node = new_ast_node(TOKEN_SUBSHELL, "()", current->is_space);
		paren_node->left = sub_expr;
		*left_node = paren_node;
	}
	*token = current;
}

int	handle_and_or(t_token **current,
	t_ast_node **left_node, int min_precedence)
{
	int			current_precedence;
	t_token		*operator_token;
	t_ast_node	*right_node;
	t_ast_node	*operator_node;

	current_precedence = get_operator_precedence((*current)->type);
	if (current_precedence < min_precedence)
		return (1);
	operator_token = *current;
	(*current) = (*current)->next;
	right_node = parser(current, current_precedence + 1);
	operator_node = new_ast_node(operator_token->type,
			operator_token->value, operator_token->is_space);
	operator_node->left = *left_node;
	operator_node->right = right_node;
	*left_node = operator_node;
	return (0);
}

int	handle__pipe(t_token **current,
	t_ast_node **left_node, int min_precedence)
{
	int			current_precedence;
	t_token		*operator_token;
	t_ast_node	*right_node;
	t_ast_node	*operator_node;

	current_precedence = get_operator_precedence((*current)->type);
	if (current_precedence < min_precedence)
		return (1);
	operator_token = *current;
	(*current) = (*current)->next;
	right_node = parser(current, current_precedence + 1);
	operator_node = new_ast_node(operator_token->type,
			operator_token->value, operator_token->is_space);
	operator_node->left = *left_node;
	operator_node->right = right_node;
	*left_node = operator_node;
	return (0);
}

int	handle_and_or_pipe(t_token **current,
	t_ast_node **left_node, int min_precedence)
{
	if ((*current)->type == TOKEN_AND || (*current)->type == TOKEN_OR)
	{
		if (handle_and_or(current, left_node, min_precedence))
			return (1);
	}
	else if ((*current)->type == TOKEN_PIPE)
	{
		if (handle__pipe(current, left_node, min_precedence))
			return (1);
	}
	return (0);
}

t_ast_node	*parser(t_token **tokens, int min_precedence)
{
	t_token		*current;
	t_ast_node	*left_node;

	current = *tokens;
	left_node = NULL;
	left_node = parse_command(&current);
	while (current && current->type != TOKEN_END)
	{
		if (current->type == TOKEN_AND || current->type == TOKEN_OR
			|| current->type == TOKEN_PIPE)
		{
			if (handle_and_or_pipe(&current, &left_node, min_precedence))
				break ;
		}
		else if (handle_parsing_redirect_norm(&current))
		{
			if (handle_parsing_redirect(&current, &left_node, min_precedence))
				break ;
		}
		else if (current->type == TOKEN_PAREN_OPEN)
			handle_subshell(&current, &left_node, min_precedence);
		else
			current = current->next;
	}
	return (*tokens = current, left_node);
}
