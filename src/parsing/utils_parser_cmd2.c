/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_cmd2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:18:24 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:44:39 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*parse_quoted_content(t_token **tokens);

void	handle_assignement_double_quote(t_token **current,
	t_ast_node **assignment_node)
{
	t_ast_node	*new_node;

	if ((*current)->type == TOKEN_DOUBLE_QUOTE
		|| (*current)->type == TOKEN_SINGLE_QUOTE)
	{
		new_node = new_ast_node((*current)->type,
				(*current)->value, (*current)->is_space);
		*current = (*current)->next;
		new_node->next = parse_quoted_content(current);
		(*assignment_node)->right = new_node;
	}
	else
	{
		(*assignment_node)->right = new_ast_node((*current)->type,
				(*current)->value, (*current)->is_space);
		(*current) = (*current)->next;
	}
}
