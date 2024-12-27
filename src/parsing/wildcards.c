/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:47:34 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 05:09:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_realloc(char **array, size_t old_size, size_t new_size)
{
	char	**new_array;

	new_array = ft_calloc(new_size + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	if (array)
	{
		ft_memcpy(new_array, array, old_size * sizeof(char *));
		free(array);
	}
	return (new_array);
}

int	handle_point(const char *pattern, const char *d_name)
{
	char	*point;

	if (*(pattern + 1) == '\0')
		return (1);
	if (*(pattern + 1) == '.')
	{
		point = ft_strchr(d_name, '.');
		if (!point)
			return (0);
		return (match_wildcard(pattern + 1, point));
	}
	if (*d_name && (match_wildcard(pattern + 1, d_name) \
		|| handle_point(pattern, d_name + 1)))
		return (1);
	return (0);
}

void	hande_single_dir(const char *dir_path, const char *file_pattern,
	char ***expanded_args, int *count)
{
	DIR				*dir;
	t_expand_info	exp_info;

	exp_info.exp_args = expanded_args;
	exp_info.count = count;
	dir = opendir(dir_path);
	if (!dir)
	{
		perror("open dir failed");
		return ;
	}
	match_and_add_file(dir, file_pattern, &exp_info, dir_path);
	closedir(dir);
}

void	handle_complex_dir(char **subdirs, char *file_pattern,
	char ***expanded_args, int *count)
{
	int				i;
	DIR				*dir;
	t_expand_info	exp_info;

	exp_info.exp_args = expanded_args;
	exp_info.count = count;
	i = 0;
	while (subdirs && subdirs[i])
	{
		dir = opendir(subdirs[i]);
		if (dir)
		{
			match_and_add_file(dir, file_pattern, &exp_info, subdirs[i]);
			closedir(dir);
		}
		free(subdirs[i]);
		i++;
	}
	free(subdirs);
}

char	**expand_wildcard_token(const char *pattern, t_shell_state *shell_state)
{
	char	**expanded_args;
	int		count;
	char	*dir_path;
	char	*file_pattern;
	char	**subdirs;

	expanded_args = NULL;
	count = 0;
	dir_path = extract_dir_path(pattern);
	expanded_args = ft_calloc(1, sizeof(char *));
	file_pattern = extract_file_pattern(pattern);
	if (!ft_strchr(dir_path, '*'))
		hande_single_dir(dir_path, file_pattern, &expanded_args, &count);
	else
	{
		subdirs = expand_wildcard_token(dir_path, shell_state);
		handle_complex_dir(subdirs, file_pattern, &expanded_args, &count);
	}
	expanded_args = ft_realloc(expanded_args, count * sizeof(char *), \
		(count + 1) * sizeof(char *));
	expanded_args[count] = NULL;
	free(dir_path);
	return (expanded_args);
}
