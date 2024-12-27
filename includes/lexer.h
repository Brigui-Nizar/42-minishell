/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:21:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/03 13:38:28 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structure.h"
# include "libft.h"

t_token	*lexer(char *input, t_shell_state *shell_state);
void	set_next_token(char *end, t_shell_state *shell_state);

char	*handle_word(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_assignment(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_blank(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_variable(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_end(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_wildcard(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_pipe(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_operator(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_parenthesis(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_redirection(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_single_quote(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_double_quote(t_token **head, t_token **current, char *input,
			t_shell_state *shell_state);
char	*handle_tilde(t_token **head,
			t_token **current, char *input, t_shell_state *shell_state);
#endif