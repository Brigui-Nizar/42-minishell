/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:02:18 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/09 09:06:38 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include "structure.h"

void	minishell_error(char *message);
void	minishell_error_status_code(char *message, int status_code,
			t_shell_state *shell_state);
void	minishell_error_copy_env(t_shell_state *shell_state);
void	minishell_exit_error_calloc(t_shell_state *shell_state);
void	minishell_exit_error_strdup(t_shell_state *shell_state);
void	minishell_error_cmd_not_found(char *cmd, t_shell_state *shell_state);
void	minishell_error_errno(t_shell_state *shell_state);
/* cd */
void	minishell_error_no_such_file_or_directory(char *dir,
			t_shell_state *shell_state);
void	minishell_error_too_many_args(char *cmd, t_shell_state *shell_state);

void	minishell_error_pipe(t_shell_state *shell_state);
/* export */
void	minishell_error_export(char *cmd, t_shell_state *shell_state);
/* PATH */
void	minishell_error_exit_no_path(void);

void	minishell_error_unexpected_token(t_shell_state *shell_state);

void	minishell_error_exit_is_directory(char *cmd,
			t_shell_state *shell_state);
void	minishell_error_exit_no_such_file_or_directory(char *cmd,
			t_shell_state *shell_state);
void	minishell_error_exit_no_permission_denied(char *cmd,
			t_shell_state *shell_state);

void	minishell_error_exit_num_args(char **args,
			t_shell_state *shell_state);

void	minishell_error_signal(int status, t_shell_state *shell_state);

#endif
