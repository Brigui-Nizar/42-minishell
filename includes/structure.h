/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:10:46 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/07 17:19:58 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "token.h"
# include "parser.h"

typedef struct s_shell_state	t_shell_state;

typedef int						(*t_ft_cmd_handler)(char **, t_shell_state *);

typedef struct s_formatHandler
{
	char					*cmd;
	t_ft_cmd_handler		handler;
	struct s_formatHandler	*next;
}							t_formatHandler;

/* Structure pour stocker les informations d'une commande
	(ex: "ls -l" ou "ls -l > file.txt" ou "ls -l | wc -l")
	(ex: "ls -l | wc -l > file.txt")
	cmd_name **args [*input_file] [*output_file] [append_output pipe] is_pipe
*/
typedef struct s_command
{
	char				*cmd_name;
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_output;
	int					is_pipe;
	struct s_command	*next;
}	t_command;

typedef struct s_env_var
{
	char				*name;
	char				*value;
	int					is_exported;
	struct s_env_var	*next;
}				t_env_var;

// Structure pour stocker l'état du shell
typedef struct s_shell_state
{
	char			**env;
	char			**set;
	t_env_var		*env_vars;
	t_env_var		*tmp_env_vars;
	int				last_exit_status;
	int				signal_received;
	int				num_commands;
	t_formatHandler	*handlers;
	char			*minishell_path;
	char			*prompt;
	char			*input;
	t_token			*tokens;
	t_token			*tokens_tmp;
	t_ast_node		*ast_root;
	int				save_stdout;
	int				save_stdin;
	int				in_double_quote;
	int				in_single_quote;
	int				in_assignement;
	int				in_parent;
	int				is_space;
}	t_shell_state;

typedef struct s_build_args
{
	t_ast_node	*tmp;
	char		**args;
	char		*str;
	int			flag_is_space;
	int			flag_waitspace;
}	t_build_args;

typedef struct s_expand_info
{
	char	***exp_args;
	int		*count;
}	t_expand_info;

void		exec_from_path(t_shell_state *shell_state, char *command,
				char **argv, char **envp);

#endif
