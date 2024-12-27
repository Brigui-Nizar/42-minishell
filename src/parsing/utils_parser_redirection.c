/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 12:03:49 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	force_redirect(t_ast_node *root, t_ast_node *new)
{
	t_token_type	last_type;

	last_type = TOKEN_ERROR;
	if ((new)->type == TOKEN_REDIRECT_OUTPUT
		|| (new)->type == TOKEN_REDIRECT_APPEND
		|| (new)->type == TOKEN_REDIRECT_INPUT
		|| (new)->type == TOKEN_HEREDOC)
	{
		while (root)
		{
			if (root->type == TOKEN_REDIRECT_OUTPUT
				|| root->type == TOKEN_REDIRECT_APPEND
				|| root->type == TOKEN_REDIRECT_INPUT
				|| root->type == TOKEN_HEREDOC)
			{
				last_type = root->type;
			}		
			root = root->next;
		}
		if (((new)->type != last_type) && last_type != TOKEN_ERROR)
			return (1);
	}
	return (0);
}

void	set_last_right_next_is_space(t_ast_node **root)
{
	t_ast_node	*tmp;
	t_ast_node	*head;

	tmp = *root;
	head = tmp;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->is_space = 1;
	*root = head;
}

int	handle_parsing_redirect(t_token **current,
	t_ast_node **left_node, int min_precedence)
{
	int			current_precedence;
	t_token		*operator_token;
	t_ast_node	*right_node;
	t_ast_node	*operator_node;

	current_precedence = get_operator_precedence((*current)->type);
	if (current_precedence < min_precedence)
		return (1);
	(void)min_precedence;
	operator_token = *current;
	(*current) = (*current)->next;
	right_node = parser(current, current_precedence + 1);
	operator_node = new_ast_node(operator_token->type,
			operator_token->value, operator_token->is_space);
	operator_node->right = right_node;
	lst_add_before_last_right(left_node, operator_node);
	return (0);
}

int	handle_parsing_redirect_norm(t_token **current)
{
	if ((*current)->type == TOKEN_REDIRECT_OUTPUT
		|| (*current)->type == TOKEN_REDIRECT_APPEND
		|| (*current)->type == TOKEN_REDIRECT_INPUT
		|| (*current)->type == TOKEN_HEREDOC)
	{
		return (1);
	}
	return (0);
}
