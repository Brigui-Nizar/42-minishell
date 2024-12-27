/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle_check_input.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:21:25 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 14:13:18 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_check_input(t_unexpected *c)
{
	if (c->pipe > 2)
		return (1);
	if (c->sup > 2)
		return (1);
	if (c->inf > 2)
		return (1);
	if (c->and > 2)
		return (1);
	if (c->inf == 1 && c->sup == 1)
		return (1);
	if (c->semicolon > 1)
		return (1);
	return (0);
}

int	handle_check_input_final(t_unexpected *c)
{
	if (c->pipe > 0)
		return (1);
	if (c->sup > 0)
		return (1);
	if (c->inf > 0)
		return (1);
	if (c->and > 0)
		return (1);
	if (c->semicolon > 0)
		return (1);
	if (c->parent != 0)
		return (1);
	return (0);
}
