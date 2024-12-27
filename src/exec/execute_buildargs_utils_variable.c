/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_utils_variable.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 05:47:10 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_args_variable(t_token_type token_type, t_ast_node *current,
	t_shell_state *shell_state, int *flag_is_space)
{
	t_env_var	*env_var;
	char		*result;

	if (ft_strlen(current->value) == 1 && ((current->next == NULL
				|| token_type == TOKEN_DOUBLE_QUOTE) || current->is_space == 1
			|| *current->next->value == ':'))
	{
		*flag_is_space = current->is_space;
		return (ft_strdup("$"));
	}
	env_var = find_env_var(shell_state->env_vars, current->value + 1);
	if (env_var)
		result = ft_strtrim(env_var->value, " ");
	else
		result = NULL;
	*flag_is_space = current->is_space;
	return (result);
}
