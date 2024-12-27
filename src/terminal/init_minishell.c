/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:39:07 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 04:33:34 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_env_var(t_env_var **head,
	const char *name, const char *value, int is_exported)
{
	t_env_var	*new;
	t_env_var	*var;

	var = find_env_var(*head, name);
	if (var)
	{
		free(var->value);
		var->value = ft_strdup(value);
		var->is_exported = is_exported;
	}
	else
	{
		new = malloc(sizeof(t_env_var));
		new->name = ft_strdup(name);
		new->value = ft_strdup(value);
		new->is_exported = is_exported;
		new->next = *head;
		*head = new;
	}
}

t_env_var	*env_list_from_array(char **env)
{
	t_env_var	*head;
	t_env_var	*new;
	t_env_var	*current;
	int			i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		new = ft_calloc(1, sizeof(t_env_var));
		new->name = get_key(env[i]);
		new->value = get_value(env[i]);
		new->is_exported = 1;
		new->next = NULL;
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	create_env_var(&head, "?", "0", 0);
	create_env_var(&head, "#", "0", 0);
	return (head);
}

/*
	This function initializes the builtins handlers
	and returns a pointer to the first element of the list
*/
t_formatHandler	*init_builtins_handlers(void)
{
	t_formatHandler	*handlers;

	handlers = NULL;
	handlers = ft_lst_builtins_new("exit", ft_exit);
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("env", ft_env));
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("set", ft_set));
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("echo", ft_echo));
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("cd", ft_cd));
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("pwd", ft_pwd));
	ft_lst_builtins_add_back(&handlers,
		ft_lst_builtins_new("export", ft_export));
	ft_lst_builtins_add_back(&handlers, ft_lst_builtins_new("unset", ft_unset));
	return (handlers);
}

void	init_minishell(t_shell_state *shell_state, char **envp)
{
	shell_state->minishell_path = NULL;
	shell_state->handlers = init_builtins_handlers();
	shell_state->minishell_path = getcwd(NULL, 0);
	if (envp == NULL || *envp == NULL)
	{
		shell_state->env_vars = NULL;
		create_env_var(&shell_state->env_vars, "?", "0", 0);
		create_env_var(&shell_state->env_vars, "HOME",
			shell_state->minishell_path, 1);
	}
	else
		shell_state->env_vars = env_list_from_array(envp);
	create_env_var(&shell_state->env_vars,
		"PWD", shell_state->minishell_path, 1);
	create_env_var(&shell_state->env_vars,
		"OLDPWD", shell_state->minishell_path, 1);
	shell_state->tmp_env_vars = shell_state->env_vars;
	shell_state->last_exit_status = 0;
	shell_state->prompt = NULL;
	shell_state->input = NULL;
	shell_state->tokens = NULL;
	shell_state->tokens_tmp = NULL;
	shell_state->ast_root = NULL;
	shell_state->save_stdin = -1;
	shell_state->save_stdout = -1;
}
