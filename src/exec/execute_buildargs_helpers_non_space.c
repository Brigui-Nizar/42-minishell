/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_helpers_non_space.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 04:13:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 11:28:25 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	norm_handle_non_space(t_ast_node **tmp, t_shell_state *shell_state,
	t_build_args *x, char **str_tmp)
{
	if ((*tmp)->type == TOKEN_WORD)
	{
		*str_tmp = ft_strdup((*tmp)->value);
	}
	else if ((*tmp)->type == TOKEN_ASSIGNMENT)
	{
		*str_tmp = handle_args_assignment((*tmp),
				shell_state, &x->flag_is_space);
	}
	else if ((*tmp)->type == TOKEN_DOUBLE_QUOTE)
	{
		*str_tmp = build_args_token_double_quote(
				tmp, shell_state, &x->flag_is_space);
	}
	else if ((*tmp)->type == TOKEN_SINGLE_QUOTE)
	{
		*str_tmp = build_args_token_single_quote(
				tmp, shell_state, &x->flag_is_space);
	}
	if (*str_tmp == NULL)
		*str_tmp = ft_strdup("");
	return (1);
}

static char	*handle_non_space(t_ast_node **tmp, t_shell_state *shell_state,
	t_build_args *x, int *i)
{
	char	*str_tmp;

	str_tmp = NULL;
	if ((*tmp)->type == TOKEN_VARIABLE)
	{
		str_tmp = handle_args_variable(TOKEN_VARIABLE,
				*tmp, shell_state, &x->flag_is_space);
		return (str_tmp);
	}
	else if ((*tmp)->type == TOKEN_WORD
		&& ft_strchr((*tmp)->value, '*') != NULL)
	{
		if ((*x).str)
		{
			(*tmp)->value = ft_strjoin_free_s1_s2((*x).str, (*tmp)->value);
			(*x).str = NULL;
		}
		expanded_wildcards_args((*tmp), &x->args, i, shell_state);
		return (NULL);
	}
	else if (norm_handle_non_space(tmp, shell_state, x, &str_tmp) == 0)
		return (str_tmp);
	return (str_tmp);
}

int	build_args_loop_non_space(t_build_args *x,
	t_shell_state *shell_state, int *n)
{
	char	*str_tmp;
	int		i;

	i = *n;
	(*x).str = NULL;
	while ((*x).tmp)
	{
		str_tmp = handle_non_space(&(*x).tmp, shell_state, x, &i);
		if (str_tmp && (*x).str)
			(*x).str = ft_strjoin_free((*x).str, str_tmp);
		else if (str_tmp && !(*x).str)
			(*x).str = ft_strdup(str_tmp);
		if ((*x).tmp && (*x).tmp->is_space == 1)
		{
			if ((*x).tmp)
				(*x).tmp = (*x).tmp->next;
			break ;
		}
		if ((*x).tmp && (*x).tmp->is_space == 0)
			(*x).tmp = (*x).tmp->next;
		if (str_tmp)
			free(str_tmp);
		str_tmp = NULL;
	}
	return (free(str_tmp), i);
}
