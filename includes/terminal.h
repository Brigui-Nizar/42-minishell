/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:40:11 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 05:42:09 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H
# include "structure.h"

void	init_minishell(t_shell_state *shell_state, char **envp);
char	*build_shell_prompt(t_shell_state *shell_state);
void	diplays_minishell_banner(int argc, char **argv);
void	update_prompt(t_shell_state *shell_state);

#endif
