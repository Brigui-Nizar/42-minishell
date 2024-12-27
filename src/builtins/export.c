/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:22:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 00:14:00 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * This function checks if the given key is a valid environment variable name.
 */
int	is_valid_env_key(char *key)
{
	int	i;

	if (ft_isdigit(key[0]))
		return (0);
	if (ft_isalpha(key[0]) || key[0] == '_')
	{
		i = 1;
		while (key[i])
		{
			if (ft_isalnum(key[i]) || key[i] == '_' || key[i] != '=')
				i++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

/*
 * This function prints all environment variables if no arguments are provided.
 */
static int	print_env_if_no_args(char **args, t_shell_state *shell_state)
{
	t_env_var	*env_vars;

	env_vars = shell_state->env_vars;
	if (!args[1])
	{
		while (env_vars)
		{
			printf("declare -x %s=\"%s\"\n", env_vars->name,
				env_vars->value);
			env_vars = env_vars->next;
		}
		return (0);
	}
	return (1);
}

void	free_all(int nb, ...);

static int	norm_export(char *value,
	char *args, t_shell_state *shell_state)
{
	char	*trim;
	char	*key;

	trim = ft_strdup(value);
	free(value);
	value = trim;
	key = get_key(args);
	if (!is_valid_env_key(key))
		return (minishell_error_export(args, shell_state), 256);
	set_env_var(&shell_state->env_vars, key, value, 1);
	free_all(2, value, key);
	return (0);
}

/*
 * The main export function that handles arguments
 *	and adds environment variables.
 */
int	ft_export(char **args, t_shell_state *shell_state)
{
	char	*value;
	int		i;

	i = 1;
	if (print_env_if_no_args(args, shell_state) == 0)
		return (0);
	while (args[i])
	{
		if (!*args[i])
			return (minishell_error_export(args[i], shell_state), 256);
		if (ft_strchr(args[i], '=') == NULL && !is_valid_env_key(args[i]))
			return (minishell_error_export(args[i], shell_state), 256);
		value = get_value(args[i]);
		if (value && *value)
		{
			if (norm_export(value, args[i], shell_state) == 256)
				return (256);
		}
		else
			export_set_env_var(&shell_state->env_vars, args[i]);
		i++;
	}
	return (0);
}

void	export_set_env_var(t_env_var **head, const char *name)
{
	t_env_var	*var;

	var = find_env_var(*head, name);
	if (var)
		var->is_exported = 1;
}
