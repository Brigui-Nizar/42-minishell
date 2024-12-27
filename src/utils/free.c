/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:57:19 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 12:52:40 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function frees the environment
*/
void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	lst_clear_env(t_env_var *env)
{
	t_env_var	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

/*
	This function frees the split
*/
void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_minishell_loop(t_shell_state *shell_state)
{
	if (shell_state->ast_root)
		free_ast(shell_state->ast_root);
	if (shell_state->tokens_tmp)
		free_tokens(shell_state->tokens_tmp);
	if (shell_state->input)
		free(shell_state->input);
	shell_state->ast_root = NULL;
	shell_state->tokens_tmp = NULL;
	shell_state->input = NULL;
}

char	*ft_strjoin_free_s1_s2(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2 + 1);
	free(s1);
	free(s2);
	return (new_str);
}
