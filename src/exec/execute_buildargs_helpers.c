/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_helpers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 07:09:02 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/04 04:29:58 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free_s1_s2(char *s1, char *s2);

t_build_args	init_build_args(t_ast_node **root)
{
	t_build_args	build_args;

	build_args.tmp = *root;
	build_args.args = ft_calloc((count_args_token(*root) + 2),
			sizeof(char *));
	build_args.str = NULL;
	build_args.flag_is_space = 0;
	build_args.flag_waitspace = 0;
	return (build_args);
}

static int	norm_handle_token(t_ast_node **tmp, t_shell_state *shell_state,
	t_build_args *x, int *i)
{
	if ((*tmp)->type == TOKEN_WORD && (*tmp)->is_space == 1)
	{
		(x->args)[*i] = ft_strdup((*tmp)->value);
		return (0);
	}
	else if ((*tmp)->type == TOKEN_ASSIGNMENT)
	{
		(x->args)[*i] = handle_args_assignment((*tmp),
				shell_state, &x->flag_is_space);
		return (0);
	}
	else if ((*tmp)->type == TOKEN_DOUBLE_QUOTE)
	{
		(x->args)[*i] = build_args_token_double_quote(tmp,
				shell_state, &x->flag_is_space);
		return (0);
	}
	else
		return (1);
}

static int	handle_token(t_ast_node **tmp, t_shell_state *shell_state,
	t_build_args *x, int *i)
{
	if ((*tmp)->type == TOKEN_VARIABLE)
	{
		(x->args)[*i] = handle_args_variable(TOKEN_VARIABLE,
				*tmp, shell_state, &x->flag_is_space);
		if ((x->args)[*i] == NULL)
		{
			if (tmp)
				(*tmp) = (*tmp)->next;
			return (1);
		}
	}
	else if ((*tmp)->type == TOKEN_WORD && ft_strchr((*tmp)->value, '*')
		&& (*tmp)->value[0] == '*')
	{
		expanded_wildcards_args((*tmp), &x->args, i, shell_state);
		i--;
	}
	else if (norm_handle_token(tmp, shell_state, x, i) == 0)
		;
	else
		return (x->flag_is_space = 0, 0);
	return ((*i)++, x->flag_is_space = 0, 0);
}

int	build_args_loop(t_build_args *x,
	t_shell_state *shell_state, int *n)
{
	int		i;

	i = *n;
	if ((*x).tmp && (*x).tmp->is_space == 1)
	{
		(*x).flag_is_space = 0;
		if (handle_token(&(*x).tmp, shell_state, x, &i))
			return (1);
		(*x).flag_is_space = 0;
		if ((*x).tmp)
			(*x).tmp = (*x).tmp->next;
	}
	else
	{
		i = build_args_loop_non_space(x, shell_state, &i);
		(*x).args[i] = (*x).str;
		i++;
		(*x).args[i] = NULL;
		(*x).str = NULL;
	}
	*n = i;
	return (0);
}
