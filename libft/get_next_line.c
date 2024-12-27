/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:42:45 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 14:13:35 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if ((2097152 * 8 * 8 * 8 < len1 + len2 + 1))
	{
		free(s1);
		s1 = NULL;
		ft_putstr_fd("Error: too big string no enough memory,", 2);
		ft_putstr_fd(" stop essyer de casser le programme\n", 2);
		return (ft_strdup(s2));
	}
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2 + 1);
	return (free(s1), new_str);
}

char	*ft_read_buffer(int fd, char **buffer)
{
	char	*line;
	int		rd_bytes;

	rd_bytes = 1;
	line = ft_strdup(*buffer);
	if (!line)
		return (NULL);
	if (ft_strchr(line, '\n'))
		return (line);
	while (rd_bytes != 0)
	{
		rd_bytes = read(fd, *buffer, BUFFER_SIZE);
		if (rd_bytes < 0)
		{
			free(line);
			return (NULL);
		}
		*(*buffer + rd_bytes) = '\0';
		line = ft_strjoin_free(line, *buffer);
		if (!line)
			return (NULL);
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	return (line);
}

char	*ft_extract_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line || !line[i])
	{
		free(line);
		return (NULL);
	}
	while (line[i] && line[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
	{
		free(line);
		return (NULL);
	}
	ft_memcpy(str, line, i);
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	free(line);
	return (str);
}

char	*ft_update_buffer(char *old_buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (old_buffer[i] && old_buffer[i] != '\n')
		i++;
	if (!old_buffer[i])
	{
		free(old_buffer);
		return (NULL);
	}
	new_buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!new_buffer)
	{
		free(old_buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (old_buffer[i])
		new_buffer[j++] = old_buffer[i++];
	free(old_buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[8192];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[fd] == NULL)
		buffer[fd] = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer[fd])
		return (NULL);
	line = ft_read_buffer(fd, &buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_extract_line(line);
	buffer[fd] = ft_update_buffer(buffer[fd]);
	return (line);
}
