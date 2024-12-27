/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:13:16 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/04 02:08:48 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_var	*find_env_var(t_env_var *head, const char *name)
{
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	set_env_var(t_env_var **head,
	const char *name, const char *value, int is_exported)
{
	t_env_var	*var;
	t_env_var	*new;

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

static int	count_env_vars_is_exported(t_env_var *head)
{
	int			count;
	t_env_var	*tmp;

	count = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->is_exported)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_list_to_array(t_env_var *head)
{
	int			count;
	t_env_var	*tmp;
	char		**env_array;
	char		*env_string;

	count = 0;
	tmp = head;
	count = count_env_vars_is_exported(head);
	env_array = malloc((count + 1) * sizeof(char *));
	tmp = head;
	count = 0;
	while (tmp)
	{
		if (tmp->is_exported)
		{
			env_string = concat_env_var(tmp->name, tmp->value);
			env_array[count++] = env_string;
		}
		tmp = tmp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

char	**set_list_to_array(t_env_var *head)
{
	int			count;
	t_env_var	*tmp ;
	char		**env_array;
	char		*env_string;

	count = 0;
	tmp = head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env_array = malloc((count + 1) * sizeof(char *));
	tmp = head;
	count = 0;
	while (tmp)
	{
		env_string = concat_env_var(tmp->name, tmp->value);
		env_array[count++] = env_string;
		tmp = tmp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}
