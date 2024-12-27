/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:15:23 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:44:30 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_operator_precedence(t_token_type type)
{
	if (type == TOKEN_AND)
		return (1);
	else if (type == TOKEN_OR)
		return (1);
	else if (type == TOKEN_PIPE)
		return (3);
	else if (type == TOKEN_ASSIGNMENT)
		return (4);
	else if (type == TOKEN_REDIRECT_OUTPUT)
		return (5);
	else if (type == TOKEN_REDIRECT_APPEND)
		return (5);
	else if (type == TOKEN_REDIRECT_INPUT)
		return (5);
	else if (type == TOKEN_HEREDOC)
		return (5);
	return (0);
}
