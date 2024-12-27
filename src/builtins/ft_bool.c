/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:26:53 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/08 18:04:27 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_bool(char **args, t_shell_state *shell_state)
{
	(void)shell_state;
	if (args[0] && ft_strcmp(args[0], "true") == 0)
		return (0);
	return (256);
}
