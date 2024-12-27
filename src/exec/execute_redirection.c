/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/13 03:37:27 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_output_to_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_append_output_to_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_input_from_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2 failed");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/* void	heredoc_input(const char *delimiter)
{
	char	*line;
	int		pipefd[2];
	char	*str;

	line = NULL;
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	str = ft_strdup("");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDIN_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("avertissement : « here-document » délimité par ", 2);
			ft_putstr_fd("la fin du fichier (au lieu de « ", 2);
			ft_putstr_fd((char *)delimiter, 2);
			ft_putstr_fd(" »)\n", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break ;
		}
		str = ft_strjoin_free(str, line);
		free(line);
	}
	write(pipefd[1], str, ft_strlen(str));
	free(str);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror("dup2 failed");
	close(pipefd[0]);
}
 */