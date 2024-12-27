/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 13:30:48 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args_token(t_ast_node *root)
{
	int	count;

	count = 0;
	while (root && (root->type == TOKEN_WORD || root->type == TOKEN_VARIABLE
			|| root->type == TOKEN_DOUBLE_QUOTE
			|| root->type == TOKEN_SINGLE_QUOTE
			|| root->type == TOKEN_ASSIGNMENT))
	{
		count++;
		root = root->next;
	}
	return (count);
}

static int	norm_handle_quotes(t_ast_node **current, t_shell_state *shell_state,
	int *flag_is_spc, char **assignement)
{
	t_ast_node	*tmp;

	tmp = *current;
	if (tmp->right->type == TOKEN_DOUBLE_QUOTE)
	{
		norm_handle_args_assignment(tmp,
			shell_state, flag_is_spc, assignement);
		return (1);
	}
	else if (tmp->right->type == TOKEN_SINGLE_QUOTE)
	{
		*flag_is_spc = tmp->is_space;
		norm_handle_args_assignment_singlequote(tmp,
			shell_state, flag_is_spc, assignement);
		return (1);
	}
	*current = tmp;
	return (0);
}

char	*handle_args_assignment(t_ast_node *current,
	t_shell_state *shell_state, int *flag_is_spc)
{
	char		*assignement;

	if (current->left->type == TOKEN_VARIABLE)
		assignement = ft_strjoin_free(handle_args_variable(TOKEN_VARIABLE,
					current->left, shell_state, flag_is_spc), "=");
	else
		assignement = ft_strjoin(current->left->value, "=");
	if (norm_handle_quotes(&current, shell_state, flag_is_spc, &assignement))
		return (assignement);
	else
	{
		if (current->right->type == TOKEN_VARIABLE)
			assignement = ft_strjoin_free_s1_s2(assignement,
					handle_args_variable(TOKEN_VARIABLE,
						current->right, shell_state, flag_is_spc));
		else
			assignement = ft_strjoin_free(assignement, current->right->value);
		current->is_space = current->right->is_space;
	}
	if (current->next)
		*flag_is_spc = current->right->is_space;
	current = current->next;
	if (current != NULL)
		current->is_space = *flag_is_spc;
	return (assignement);
}

char	*build_args_token_double_quote(t_ast_node **current,
	t_shell_state *shell_state, int *flag_is_spc)
{
	char		*arg;
	char		*arg_tmp;
	t_ast_node	*tmp;

	tmp = *current;
	if (tmp->type == TOKEN_DOUBLE_QUOTE)
	{
		tmp = tmp->next;
		arg = ft_strdup("");
		while (tmp && tmp->type != TOKEN_DOUBLE_QUOTE)
		{
			if (tmp->type == TOKEN_VARIABLE)
				arg_tmp = handle_args_variable(TOKEN_DOUBLE_QUOTE,
						tmp, shell_state, flag_is_spc);
			else if (tmp->type == TOKEN_WORD)
				arg_tmp = ft_strdup(tmp->value);
			else if (tmp->type == TOKEN_ASSIGNMENT)
				arg_tmp = handle_args_assignment(tmp, shell_state, flag_is_spc);
			if (arg_tmp == NULL)
				arg_tmp = ft_strdup("");
			arg = ft_strjoin_free_s1_s2(arg, arg_tmp);
			tmp = tmp->next;
		}
	}
	return (*current = tmp, arg);
}

char	*build_args_token_single_quote(t_ast_node **current,
	t_shell_state *shell_state, int *flag_is_spc)
{
	char		*arg;
	char		*arg_tmp;
	t_ast_node	*tmp;

	tmp = *current;
	if (tmp->type == TOKEN_SINGLE_QUOTE)
	{
		tmp = tmp->next;
		arg = ft_strdup("");
		while (tmp && tmp->type != TOKEN_SINGLE_QUOTE)
		{
			if (tmp->type == TOKEN_VARIABLE)
				arg_tmp = handle_args_variable(TOKEN_SINGLE_QUOTE,
						tmp, shell_state, flag_is_spc);
			else if (tmp->type == TOKEN_WORD)
				arg_tmp = ft_strdup(tmp->value);
			else if (tmp->type == TOKEN_ASSIGNMENT)
				arg_tmp = handle_args_assignment(tmp, shell_state, flag_is_spc);
			arg = ft_strjoin_free(arg, arg_tmp);
			free(arg_tmp);
			tmp = tmp->next;
		}
		*current = tmp;
	}
	return (arg);
}
