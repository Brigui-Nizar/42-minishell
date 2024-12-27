/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_buildargs_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:29:16 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:45:05 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	norm_handle_args_assignment(t_ast_node *current,
	t_shell_state *shell_state, int *flag_is_spc, char **assignement)
{
	char		*tmp2;
	t_ast_node	*tmp;

	tmp = current->right;
	tmp2 = build_args_token_double_quote(&tmp, shell_state, flag_is_spc);
	*assignement = ft_strjoin_free(*assignement, tmp2);
	free(tmp2);
	current->is_space = tmp->is_space;
	current = current->next;
}

void	norm_handle_args_assignment_singlequote(t_ast_node *current,
	t_shell_state *shell_state, int *flag_is_spc, char **assignement)
{
	char		*tmp2;
	t_ast_node	*tmp;

	tmp = current->right;
	tmp2 = build_args_token_single_quote(&tmp, shell_state, flag_is_spc);
	*assignement = ft_strjoin_free(*assignement, tmp2);
	free(tmp2);
	current->is_space = tmp->is_space;
	current = current->next;
}
