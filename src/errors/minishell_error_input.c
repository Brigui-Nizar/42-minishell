/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:52:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/30 00:47:45 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	minishell_error_unexpected_token(t_shell_state *shell_state)
{
	ft_putstr_fd("minishell: syntax error", STDERR_FILENO);
	ft_putstr_fd(" near unexpected token `", STDERR_FILENO);
	ft_putchar_fd(is_unexpected_token(shell_state->input), STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	update_set(shell_state, "?", "2");
}
