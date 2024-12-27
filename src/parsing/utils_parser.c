/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:46:37 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/06 14:39:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* Create a new AST node
* type: the type of the token
* value: the value of the token
* is_space: if the token is followed by a space
* return: the new AST node malloced
*/
t_ast_node	*new_ast_node(t_token_type type, char *value, int is_space)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = type;
	node->is_space = is_space;
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->next = NULL;
	return (node);
}

/*
* Free the AST recursively
*/
void	free_ast(t_ast_node *root)
{
	t_ast_node	*tmp;

	tmp = root;
	if (tmp)
	{
		free_ast(root->left);
		free_ast(root->right);
		free_ast(root->next);
		if (root->value)
			free(root->value);
		free(tmp);
	}
}

/*
** DEBUG FUNCTIONS
* print_ast: print the AST
*/
void	print_ast(t_ast_node *root, int level)
{
	int	i;

	i = 0;
	if (!root)
		return ;
	while (i < level && i < 10)
	{
		ft_putstr_fd("  ", 2);
		i++;
	}
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(RED, 2);
	ft_putnbr_fd(root->type, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(root->value, 2);
	ft_putstr_fd(" is_space ", 2);
	ft_putnbr_fd(root->is_space, 2);
	ft_putstr_fd("\n", 2);
	print_ast(root->left, level + 1);
	print_ast(root->right, level + 1);
	if (root->next)
		print_ast(root->next, level);
}

void	lst_add_back(t_ast_node **lst, t_ast_node *new)
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
	return ;
}
