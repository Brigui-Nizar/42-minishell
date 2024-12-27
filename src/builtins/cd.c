/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:39:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 08:17:08 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static char	*helper_pwd(t_shell_state *shell_state)
{
	char		*pwd;
	t_env_var	*env_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		env_var = find_env_var(shell_state->env_vars, "PWD");
		if (!env_var)
		{
			perror("getcwd");
			return (NULL);
		}
		pwd = ft_strjoin(env_var->value, "/..");
	}
	return (pwd);
}

static char	*helper_oldpwd(t_shell_state *shell_state, char *get_path)
{
	t_env_var	*env_var;

	if (!get_path)
	{
		env_var = find_env_var(shell_state->env_vars, "OLDPWD");
		if (!env_var)
		{
			perror("getcwd");
			return (NULL);
		}
		get_path = ft_strdup(env_var->value);
	}
	return (get_path);
}

static void	set_pwd(t_shell_state *shell_state, char *get_path)
{
	char		*pwd;

	pwd = helper_pwd(shell_state);
	get_path = helper_oldpwd(shell_state, get_path);
	set_env_var(&shell_state->env_vars, "OLDPWD", get_path, 1);
	set_env_var(&shell_state->env_vars, "PWD", pwd, 1);
	free(pwd);
}

int	ft_cd(char **args, t_shell_state *shell_state)
{
	char	*get_path;

	get_path = getcwd(NULL, 0);
	if (count_args(args) > 3)
	{
		minishell_error_too_many_args("cd", shell_state);
		return (free(get_path), 1);
	}
	if (!args[1] || ft_strncmp(args[1], "~", ft_strlen(args[1])) == 0)
	{
		set_env_var(&shell_state->env_vars, "OLDPWD", get_path, 1);
		chdir(shell_state->minishell_path);
		set_env_var(&shell_state->env_vars, "PWD",
			shell_state->minishell_path, 1);
		return (free(get_path), 0);
	}
	if (chdir(args[1]) != 0)
	{
		minishell_error_no_such_file_or_directory(args[1], shell_state);
		return (free(get_path), 256);
	}
	else
		set_pwd(shell_state, get_path);
	return (free(get_path), 0);
}
