/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_wildcards.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 05:12:36 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**expand_wildcard_token(const char *token, t_shell_state *shell_state);
char	**ft_realloc(char **array, size_t old_size, size_t new_size);
void	bubble_sort_natural(char **array);

static char	**handler_expanded_wildcards_args(int *n,
	char **expanded_args, char **args_tmp)
{
	int		j;
	int		i;

	i = *n;
	j = 0;
	while (expanded_args[j])
	{
		args_tmp[i] = ft_strdup(expanded_args[j]);
		i++;
		j++;
	}
	free_split(expanded_args);
	args_tmp[i] = NULL;
	*n = i;
	return (args_tmp);
}

static void	expanded_args_match_wildcards(t_ast_node	*tmp,
	char ***args, int *n, t_shell_state *shell_state)
{
	char	**expanded_args;
	int		len;
	int		i;
	char	**args_tmp;

	args_tmp = *args;
	i = *n;
	expanded_args = expand_wildcard_token(tmp->value, shell_state);
	bubble_sort_natural(expanded_args);
	len = args_len(expanded_args);
	if (len > 0)
	{
		args_tmp = ft_realloc(*args, i, (i + len));
		args_tmp = handler_expanded_wildcards_args(&i,
				expanded_args, args_tmp);
	}
	else
	{
		args_tmp[i] = ft_strdup(tmp->value);
		i++;
		free_split(expanded_args);
	}
	*n = i;
	*args = args_tmp;
}

void	expanded_wildcards_args(t_ast_node	*tmp,
	char ***args, int *n, t_shell_state *shell_state)
{
	int		i;
	char	**args_tmp;

	args_tmp = *args;
	i = *n;
	if (ft_strchr(tmp->value, '*') || ft_strchr(tmp->value, '?'))
	{
		expanded_args_match_wildcards(tmp, args, &i, shell_state);
		*n = i;
		return ;
	}
	else
		args_tmp[i] = ft_strdup(tmp->value);
	*n = i;
	*args = args_tmp;
}

void	handle_args_wildcard(t_ast_node *current,
	t_shell_state *shell_state,	char ***args, int i)
{
	*args[i] = ft_strdup(current->value);
	expanded_wildcards_args(current, args, &i, shell_state);
}
