/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:42:31 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 08:35:30 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_prompt(t_shell_state *shell_state)
{
	g_unblock_sigquit = 0;
	if (shell_state->prompt)
		free(shell_state->prompt);
	shell_state->prompt = build_shell_prompt(shell_state);
}

static char	*build_promt_ablosute_path(char *dir_path)
{
	char	*minishell_promt;

	minishell_promt = ft_strjoin(GREEN, "minishell");
	minishell_promt = ft_strjoin_free(minishell_promt, RESET);
	minishell_promt = ft_strjoin_free(minishell_promt, ":");
	minishell_promt = ft_strjoin_free(minishell_promt, BLUE);
	minishell_promt = ft_strjoin_free(minishell_promt, dir_path);
	minishell_promt = ft_strjoin_free(minishell_promt, RESET);
	minishell_promt = ft_strjoin_free(minishell_promt, "$ ");
	return (minishell_promt);
}

static char	*build_prompt_relative_path(char *dir_path, char *home_path)
{
	char	*minishell_promt;
	char	*sub_dir_path;

	sub_dir_path = ft_substr(dir_path, ft_strlen(home_path),
			ft_strlen(dir_path));
	if (!sub_dir_path)
	{
		free(dir_path);
		return (NULL);
	}
	minishell_promt = ft_strjoin(GREEN, "minishell");
	minishell_promt = ft_strjoin_free(minishell_promt, RESET);
	minishell_promt = ft_strjoin_free(minishell_promt, ":");
	minishell_promt = ft_strjoin_free(minishell_promt, BLUE);
	minishell_promt = ft_strjoin_free(minishell_promt, "~");
	minishell_promt = ft_strjoin_free(minishell_promt, sub_dir_path);
	minishell_promt = ft_strjoin_free(minishell_promt, RESET);
	minishell_promt = ft_strjoin_free(minishell_promt, "$ ");
	free(sub_dir_path);
	return (minishell_promt);
}
void	free_all(int count, ...);

char	*build_shell_prompt(t_shell_state *shell_state)
{
	char		*minishell_promt;
	char		*dir_path;
	char		*home_path;
	t_env_var	*home_var;

	dir_path = getcwd(NULL, 0);
	if (!dir_path)
	{
		dir_path = find_env_var(shell_state->env_vars, "PWD")->value;
		return (build_promt_ablosute_path(dir_path));
	}
	home_var = find_env_var(shell_state->env_vars, "HOME");
	if (!home_var)
	{
		minishell_promt = build_promt_ablosute_path(dir_path);
		return (free(dir_path), minishell_promt);
	}
	home_path = ft_strdup(home_var->value);
	if (home_path && ft_strcmp(home_path, dir_path) <= 0)
		minishell_promt = build_prompt_relative_path(dir_path, home_path);
	else if (ft_strcmp(home_path, dir_path) > 0)
		minishell_promt = build_promt_ablosute_path(dir_path);
	free_all(2, dir_path, home_path);
	return (minishell_promt);
}
