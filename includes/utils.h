/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:27:36 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 04:32:51 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "structure.h"

int		is_valid_input(char *input, t_shell_state *shell_state);
void	print_args(char **args);
int		args_len(char **args);

int		are_quotes_closed(const char *line);
char	*get_complete_input(char *initial_input);
void	exit_shell(t_shell_state *shell_state, int status_code);

void	close_fds(t_shell_state *shell_state);

#endif
