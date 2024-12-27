/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:27:36 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/10 16:04:20 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdarg.h>
# include <errno.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structure.h"
# include "builtins.h"
# include "colors.h"
# include "signals.h"
# include "free.h"
# include "env.h"
# include "terminal.h"
# include "lexer.h"
# include "parser.h"
# include "errors.h"
# include "exec.h"
# include "utils.h"
# include "is_unexpected.h"

extern volatile sig_atomic_t	g_unblock_sigquit;

//extern volatile sig_atomic_t g_sigint_received; //= 0;
//extern volatile sig_atomic_t g_sigquit_received;// = 0;

t_formatHandler	*ft_lst_builtins_new(char *specifier, t_ft_cmd_handler handler);
void			ft_lst_builtins_add_back(t_formatHandler **lst,
					t_formatHandler *new);
void			ft_lst_builtins_clear(t_formatHandler **lst,
					void (*del)(void *));

void			set_exit_status(t_shell_state *shell_state, int status);
#endif
