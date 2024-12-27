/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser_redirec_add.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:53:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 12:03:45 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lst_add_front_last_right(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new;
}

static void	lst_add_before_last_first_token_word(t_ast_node **lst,
	t_ast_node *new)
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
	while (tmp->next && (tmp->next->type != TOKEN_WORD
			&& tmp->next->type != TOKEN_VARIABLE
			&& tmp->next->type != TOKEN_SINGLE_QUOTE
			&& tmp->next->type != TOKEN_DOUBLE_QUOTE))
			tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
}

static int	norm2(t_ast_node **lst, t_ast_node *new, t_ast_node *tmp)
{
	if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_VARIABLE
		|| tmp->type == TOKEN_SINGLE_QUOTE
		|| tmp->type == TOKEN_DOUBLE_QUOTE)
	{
		if (new->right->is_space == 1 && new->right->next != NULL)
		{
			if (new->right->next != NULL)
			{
				ast_add_back(lst, new->right->next);
				new->right->next = NULL;
			}
			lst_add_front_last_right(lst, new);
			return (1);
		}
		set_last_right_next_is_space(lst);
		lst_add_front(lst, new);
		return (1);
	}
	return (0);
}

static int	norm3(t_ast_node **lst, t_ast_node *new)
{
	if (new->right != NULL)
	{
		if (force_redirect(*lst, new))
		{
			lst_add_before_last_first_token_word(lst, new);
			return (1);
		}
		else
		{
			if (new->right->next != NULL)
			{
				ast_add_back(lst, new->right->next);
				new->right->next = NULL;
			}
			lst_add_front_last_right(lst, new);
			return (1);
		}
	}
	return (0);
}

void	lst_add_before_last_right(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*tmp;

	tmp = *lst;
	if (!tmp)
	{		
		*lst = new;
		if (new->right->is_space == 1)
		{
			if (new->right->next != NULL)
			{
				ast_add_back(lst, new->right->next);
				(*lst)->right->next = NULL;
			}
			return ;
		}
		return ;
	}
	if (norm2(lst, new, tmp))
		return ;
	if (norm3(lst, new))
		return ;
	set_last_right_next_is_space(lst);
	lst_add_front(lst, new);
	return ;
}
