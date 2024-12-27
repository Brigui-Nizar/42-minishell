/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_unexpected.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:27:36 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 10:36:05 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_UNEXPECTED_H
# define IS_UNEXPECTED_H
# include "structure.h"

typedef struct s_unexpected
{
	int	sup;
	int	inf;
	int	pipe;
	int	and;
	int	semicolon;
	int	parent_open;
	int	parent_close;
	int	parent;

}	t_unexpected;

void	update_quotes_state(char c,	int *in_single_quote,
			int *in_double_quote, int *i);
char	handle_quotes(const char *line, int *i, char quote, t_unexpected *c);
char	handle_no_quotes(const char *line, int *i, t_unexpected *c);
int		is_unexpected_input(t_shell_state *shell_state);
char	is_unexpected_token(const char *line);

#endif
