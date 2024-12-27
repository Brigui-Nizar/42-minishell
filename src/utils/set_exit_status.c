/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:56:56 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/12 14:59:39 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_exit_status(t_shell_state *shell_state, int status)
{
	char	*exit_status;

	exit_status = ft_itoa(status);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
}
