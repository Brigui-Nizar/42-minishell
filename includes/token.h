/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:21:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/27 08:26:46 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_VARIABLE,
	TOKEN_ASSIGNMENT,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_OPERATOR,
	TOKEN_REDIRECT_OUTPUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_INPUT,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_OPEN,
	TOKEN_PAREN_CLOSE,
	TOKEN_SUBSHELL,
	TOKEN_WILDCARD,
	TOKEN_END,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				is_space;
	struct s_token	*next;
}	t_token;

typedef struct s_shell_state	t_shell_state;

t_token	*new_token(t_token_type type, char *value, t_shell_state *shell_state);

void	free_tokens(t_token *head);
void	print_tokens(t_token *head);

#endif 