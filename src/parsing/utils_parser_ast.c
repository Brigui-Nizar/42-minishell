/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:58:06 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 12:01:29 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ast_add_back(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	lst_add_front(t_ast_node **lst, t_ast_node *new)
{
	new->next = *lst;
	*lst = new;
}

void	lst_add_before_last(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	if (!tmp->next)
	{
		new->next = tmp;
		*lst = new;
		return ;
	}
	while (tmp->next->next)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}
