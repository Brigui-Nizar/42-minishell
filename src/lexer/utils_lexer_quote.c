/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/04 02:08:14 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static void	lexer_if_token_word(t_token **head,
	t_token **current, char *value, t_shell_state *shell_state)
{
	t_token	*new;

	if (value && *value != '\0')
	{
		new = new_token(TOKEN_WORD, value, shell_state);
		if (!*head)
			*head = new;
		else
			(*current)->next = new;
		*current = new;
	}
	else
		free(value);
}

char	*lexer_quote(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	if (*input == '"')
		return (lexer_double_quote(head, current, input, shell_state));
	else
		return (lexer_single_quote(head, current, input));
}

char	*lexer_double_quote(t_token **head,
	t_token **current, char *input, t_shell_state *shell_state)
{
	char		*start;
	char		*end;
	char		*value;
	static char	*str = NULL;

	start = input + 1;
	end = ft_strchr(start, '\"');
	if (end == NULL)
	{
		start = ft_strjoin(start, "\n");
		while (str == NULL || strchr(str, '"') == NULL)
		{
			str = get_next_line(0);
			start = ft_strjoin(start, str);
			end = ft_strchr(start, '"');
		}
	}
	value = ft_strndup(start, end - start);
	lexer_if_token_word(head, current, value, shell_state);
	return (end + 1);
}

char	*lexer_single_quote(t_token **head, t_token **current, char *input)
{
	char		*start;
	char		*end;
	char		*value;
	static char	*str = NULL;

	start = input + 1;
	end = ft_strchr(start, '\'');
	if (end == NULL)
	{
		start = ft_strjoin(start, "\n");
		while (str == NULL || strchr(str, '\'') == NULL)
		{
			str = get_next_line(0);
			start = ft_strjoin(start, str);
			end = ft_strchr(start, '\'');
		}
	}
	value = ft_strndup(start, end - start);
	lexer_if_token_word(head, current, value, NULL);
	return (end + 1);
}
 */