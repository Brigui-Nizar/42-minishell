/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:23:31 by rtorres           #+#    #+#             */
/*   Updated: 2024/10/14 13:44:51 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_exec_assignment(t_ast_node *root, t_shell_state *shell_state)
{
	char	**args;

	args = build_args(&root, shell_state);
	if (root->right->type == TOKEN_DOUBLE_QUOTE)
		args = build_args(&root->right->right, shell_state);
	else
	{
		while (root && root->type == TOKEN_ASSIGNMENT)
		{
			if (ft_isdigit(*root->left->value))
				return (minishell_error_cmd_not_found(root->left->value,
						shell_state), 127);
			update_set(shell_state, root->left->value, root->right->value);
			root = root->next;
		}
		if (root && root->type == TOKEN_WORD)
			execute_ast(root, shell_state);
	}
	free_args(args);
	return (0);
}
