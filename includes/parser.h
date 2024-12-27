/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:21:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 12:04:37 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "structure.h"

typedef struct s_expand_info	t_expand_info;

typedef struct s_ast_node
{
	t_token_type		type;
	char				*value;
	int					is_space;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*next;
}	t_ast_node;

void		print_ast(t_ast_node *root, int level);
void		free_ast(t_ast_node *root);
t_ast_node	*new_ast_node(t_token_type type, char *value, int is_space);
void		lst_add_back(t_ast_node **lst, t_ast_node *new);
t_ast_node	*parser(t_token **tokens, int min_precedence);
t_ast_node	*parse_command(t_token **tokens);
/* utils Wildcard*/
char		**ft_realloc(char **array, size_t old_size, size_t new_size);
int			handle_point(const char *pattern, const char *d_name);
void		hande_single_dir(const char *dir_path, const char *file_pattern,
				char ***expanded_args, int *count);
void		handle_complex_dir(char **subdirs, char *file_pattern,
				char ***expanded_args, int *count);
void		handle_assignement_double_quote(t_token **current,
				t_ast_node **assignment_node);

void		match_and_add_file(DIR *dir, const char *file_pattern,
				t_expand_info *exp_info, const char *dir_path);
int			match_wildcard(const char *pattern, const char *d_name);
int			match_char(const char *pattern, const char *d_name);

char		*extract_dir_path(const char *pattern);
char		*extract_file_pattern(const char *pattern);

int			get_operator_precedence(t_token_type type);
int			handle_parsing_redirect(t_token **current,
				t_ast_node **left_node, int min_precedence);
int			handle_parsing_redirect_norm(t_token **current);

void		lst_add_before_last_right(t_ast_node **lst, t_ast_node *new);

void		ast_add_back(t_ast_node **lst, t_ast_node *new);
void		lst_add_front(t_ast_node **lst, t_ast_node *new);
void		lst_add_before_last(t_ast_node **lst, t_ast_node *new);
void		set_last_right_next_is_space(t_ast_node **root);
int			force_redirect(t_ast_node *root, t_ast_node *new);

#endif
