/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 13:34:32 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**build_args(t_ast_node **root, t_shell_state *shell_state)
{
	int				i;
	t_build_args	x;

	i = 0;
	x = init_build_args(root);
	while (x.tmp && x.tmp->type != TOKEN_END)
	{
		if (build_args_loop(&x, shell_state, &i))
			continue ;
	}
	if (0 && x.str && *(x.str))
	{
		x.args[i] = ft_strdup(x.str);
		i++;
	}
	free(x.str);
	return (x.args);
}

/*
	build args from tokens
*//* 
char	**build_args(t_ast_node **root, t_shell_state *shell_state)
{
	char		**args;
	t_ast_node	*tmp;
	int			i;
	char *str;
	int flag_is_space;

	i = count_args_token(*root);
	args = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	tmp = *root;
	str = ft_strdup("");
	flag_is_space = 0;
	while (tmp && tmp->type != TOKEN_END)
	{
			
		if (tmp->is_space == 1 || flag_is_space == 1)
		{
			if (flag_is_space == 1)
			{	args[i] = str;
				str = ft_strdup("");
				i++;}
			if (tmp->type == TOKEN_VARIABLE)
			{
				args[i] =  ft_strjoin_free_s1_s2(str,
					handle_args_variable(tmp, shell_state, &flag_is_space));
				if (args[i] == NULL)
				{	if (tmp)
					tmp = tmp->next;
					continue;
				}
				
			}
			else if (tmp->type == TOKEN_WORD && ft_strchr(tmp->value, '*'))
				expanded_wildcards_args(tmp, &args, &i, shell_state);
			else if (tmp->type == TOKEN_WORD)
				args[i] =  ft_strjoin_free_s1_s2(str, ft_strdup(tmp->value));
			else if (tmp->type == TOKEN_ASSIGNMENT)
				args[i] =  ft_strjoin_free_s1_s2(str,
					handle_args_assignment(tmp, shell_state, &flag_is_space));
			else if (tmp->type == TOKEN_DOUBLE_QUOTE)
				args[i] =  ft_strjoin_free_s1_s2(str,
					build_args_token_double_quote(&tmp, shell_state,
					&flag_is_space));
			str = ft_strdup("");
			i++;
			flag_is_space = 0;
		}
		else
		{
			char *str_tmp = NULL;
			if (tmp->type == TOKEN_VARIABLE)
				str_tmp = handle_args_variable(tmp, shell_state,
					&flag_is_space);
			else if (tmp->type == TOKEN_WORD
				&& ft_strchr(tmp->value, '*')!=NULL)
				expanded_wildcards_args(tmp, &args, &i, shell_state);
			else if (tmp->type == TOKEN_WORD)
				str_tmp = ft_strdup(tmp->value);
			else if (tmp->type == TOKEN_ASSIGNMENT)
				str_tmp = handle_args_assignment(tmp, shell_state,
					&flag_is_space);
			else if (tmp->type == TOKEN_DOUBLE_QUOTE)
				str_tmp = build_args_token_double_quote(&tmp,
					shell_state, &flag_is_space);
			if (str_tmp == NULL)
				str_tmp = ft_strdup("");
			str = ft_strjoin_free(str, str_tmp);
			free(str_tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (str && *str)
		args[i] = ft_strdup(str);
	free(str);
	return (args);
}
 */