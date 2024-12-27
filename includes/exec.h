/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:21:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 13:04:34 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "structure.h"

int				execute_ast(t_ast_node *root, t_shell_state *shell_state);
int				handle_exec_assignment(t_ast_node *root,
					t_shell_state *shell_state);
int				execute_pipe(t_ast_node *left, t_ast_node *right,
					t_shell_state *shell_state);
void			execute_subshell(t_ast_node *subshell_node,
					t_shell_state *shell_state);
int				execute_command(char *cmd, char **args,
					t_shell_state *shell_state);
/* build_args */
char			**build_args(t_ast_node **root, t_shell_state *shell_state);
/* build_args _ helpers */
int				build_args_loop(t_build_args *x, t_shell_state *shell_state,
					int *n);
t_build_args	init_build_args(t_ast_node **root);

/* build_args _ utils */
int				count_args_token(t_ast_node *root);
char			*handle_args_variable(t_token_type token_type,
					t_ast_node *current, t_shell_state *shell_state,
					int *flag_is_space);
char			*handle_args_word(t_ast_node *current);
char			*handle_args_assignment(t_ast_node *current,
					t_shell_state *shell_state, int *flag_is_space);
char			*build_args_token_double_quote(t_ast_node **current,
					t_shell_state *shell_state, int *flag_is_space);
char			*build_args_token_single_quote(t_ast_node **current,
					t_shell_state *shell_state, int *flag_is_space);
void			norm_handle_args_assignment(t_ast_node *current,
					t_shell_state *shell_state, int *flag_is_spc,
					char **assignement);
void			norm_handle_args_assignment_singlequote(t_ast_node *current,
					t_shell_state *shell_state, int *flag_is_spc,
					char **assignement);
/* build_args _ wildcard*/
void			handle_args_wildcard(t_ast_node *current,
					t_shell_state *shell_state, char ***args, int i);
void			expanded_wildcards_args(t_ast_node	*tmp, char ***args, int *n,
					t_shell_state *shell_state);
/* build_args _ non_space*/
int				build_args_loop_non_space(t_build_args *x,
					t_shell_state *shell_state, int *n);
/*  utils*/
void			free_args(char **args);
void			save_fds(t_shell_state *shell_state);
void			restore_fds(t_shell_state *shell_state);
/* redirection */
int				redirect_output_to_file(const char *filename);
int				redirect_append_output_to_file(const char *filename);
int				redirect_input_from_file(const char *filename);
void			heredoc_input(t_shell_state *shell_state,
					const char *delimiter);
void			norm_heredoc_input(t_ast_node *root,
					t_shell_state *shell_state);
/* operator */
void			execute_and(t_ast_node *left, t_ast_node *right,
					t_shell_state *shell_state);
void			execute_or(t_ast_node *left, t_ast_node *right,
					t_shell_state *shell_state);
/* EXECUTE HERDOC*/
void			handle_heredoc_error(const char *delimiter);
int				**ppipe(void);
int				init_pipe(int pipefd[2]);

#endif