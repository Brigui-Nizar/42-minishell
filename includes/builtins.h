/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:31:40 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/24 01:30:48 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "structure.h"

int		execute_handler_function(char **p,
			t_formatHandler *handlers, t_shell_state *shell_state);
int		ft_echo(char **args, t_shell_state *shell_state);
int		ft_cd(char **args, t_shell_state *shell_state);
int		ft_pwd(char **args, t_shell_state *shell_state);
int		ft_export(char **args, t_shell_state *shell_state);
int		ft_unset(char **args, t_shell_state *shell_state);
int		ft_env(char **args, t_shell_state *shell_state);
int		ft_set(char **args, t_shell_state *shell_state);
int		ft_exit(char **args, t_shell_state *shell_state);
int		ft_bool(char **args, t_shell_state *shell_state);

void	update_set(t_shell_state *shell_state, char *key, char *value);
void	unset_env_var(t_env_var **head, const char *name);
void	export_set_env_var(t_env_var **head, const char *name);

#endif