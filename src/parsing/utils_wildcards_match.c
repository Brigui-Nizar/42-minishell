/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:47:34 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 14:39:16 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	match_char(const char *pattern, const char *d_name)
{
	if (*pattern == '?')
	{
		if (!*d_name)
			return (0);
		return (match_wildcard(pattern + 1, d_name + 1));
	}
	if (*pattern == *d_name)
		return (match_wildcard(pattern + 1, d_name + 1));
	return (0);
}

int	match_wildcard(const char *pattern, const char *d_name)
{
	if (!*pattern)
		return (*d_name == '\0');
	if (*pattern == '*')
		return (handle_point(pattern, d_name));
	return (match_char(pattern, d_name));
}

static void	build_full_path(char *full_path, const char *dir_path,
	const char *file_name)
{
	full_path[0] = '\0';
	if (dir_path[0] != '/' && ft_strncmp(dir_path, "./", 2) != 0)
		ft_strcpy(full_path, "./");
	ft_strcat(full_path, dir_path);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, file_name);
}

static void	add_to_expanded_args(t_expand_info *exp_info, const char *full_path)
{
	*exp_info->exp_args = ft_realloc(*exp_info->exp_args, \
		(*exp_info->count) * sizeof(char *), \
		((*exp_info->count) + 1) * sizeof(char *));
	(*exp_info->exp_args)[(*exp_info->count)++] = ft_strdup(full_path);
}

void	match_and_add_file(DIR *dir, const char *f_pattern,
	t_expand_info *exp_info, const char *dir_path)
{
	struct dirent	*entry;
	char			full_path[1024];

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (*(entry->d_name) != '.' && match_wildcard(f_pattern, entry->d_name))
		{
			if (ft_strcmp(dir_path, ".") == 0)
				ft_strcpy(full_path, entry->d_name);
			else
				build_full_path(full_path, dir_path, entry->d_name);
			add_to_expanded_args(exp_info, full_path);
		}
		entry = readdir(dir);
	}
}
