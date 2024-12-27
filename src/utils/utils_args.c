/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:13:09 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 04:06:52 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	args_len(char **args)
{
	int	i;

	i = 0;
	if (*args)
	{
		while (args[i])
			i++;
	}
	return (i);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (*args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
	args = NULL;
}

/*
	print_args: print args[] array
	while args[i] is not NULL, print args[i] and increment i
*/
void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
}
