/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcards_extract.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:47:34 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 14:38:45 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_dir_path(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (last_slash != NULL)
		return (ft_strndup(pattern, last_slash - pattern));
	else
		return (ft_strdup("."));
}

char	*extract_file_pattern(const char *pattern)
{
	char	*last_slash;

	last_slash = ft_strrchr(pattern, '/');
	if (last_slash != NULL)
		return (last_slash + 1);
	else
		return ((char *)pattern);
}
