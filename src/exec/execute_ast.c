/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:43:39 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 13:02:29 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_exec_command(t_ast_node *root, t_shell_state *shell_state)
{
	char	**args;
	int		status;
	char	*exit_status;

	exit_status = NULL;
	args = build_args(&root, shell_state);
	status = execute_command(args[0], args, shell_state);
	if (WIFEXITED(status))
		exit_status = ft_itoa(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		minishell_error_signal(status, shell_state);
		exit_status = ft_itoa(128 + WTERMSIG(status));
	}
	else
		exit_status = ft_itoa(-1);
	update_set(shell_state, "?", exit_status);
	free(exit_status);
	free_args(args);
	return (status);
}

void	free_all(int nb, ...);

static int	hdle_exec_redir_arg(t_ast_node **root,
	t_shell_state *shell_state, int (*ft_redir)(const char *))
{
	char	**args;
	int		error;

	if ((*root)->right->type == TOKEN_VARIABLE)
	{
		args = build_args(&(*root)->right, shell_state);
		error = ft_redir(args[0]);
		free_args(args);
	}
	else
		error = ft_redir((*root)->right->value);
	if ((*root)->right != NULL && (*root)->right->right != NULL)
	{
		free_all(2, (*root)->right->value, (*root)->right);
		(*root)->right = (*root)->right->right;
		error = hdle_exec_redir_arg(&(*root)->right, shell_state, ft_redir);
	}
	return (error);
}

static int	handle_exec_redirection(t_ast_node *root,
	t_shell_state *shell_state)
{
	int	error;

	save_fds(shell_state);
	error = 0;
	if (root->type == TOKEN_REDIRECT_OUTPUT)
		error = hdle_exec_redir_arg(&root, shell_state,
				redirect_output_to_file);
	else if (root->type == TOKEN_REDIRECT_APPEND)
		error = hdle_exec_redir_arg(&root, shell_state,
				redirect_append_output_to_file);
	else if (root->type == TOKEN_REDIRECT_INPUT)
		error = hdle_exec_redir_arg(&root, shell_state,
				redirect_input_from_file);
	else if (root->type == TOKEN_HEREDOC)
		norm_heredoc_input(root, shell_state);
	if (ft_strcmp("130", find_env_var(shell_state->env_vars, "?")->value) == 0)
		return (restore_fds(shell_state), 0);
	if (error)
		set_exit_status(shell_state, error);
	if (!error && root->right && root->right->next)
		execute_ast(root->right->next, shell_state);
	if (!error && root->next)
		execute_ast(root->next, shell_state);
	return (0);
}

static int	create_status_signal(int status)
{
	int	status_signal;

	if (WIFSIGNALED(status))
	{
		status_signal = WTERMSIG(status) & 0x7F;
		status_signal |= 0x80;
		return (status_signal);
	}
	return (status);
}

int	execute_ast(t_ast_node *root, t_shell_state *shell_state)
{
	if (!root)
		return (0);
	if (root->type == TOKEN_ASSIGNMENT)
		return (handle_exec_assignment(root, shell_state));
	if ((root->type == TOKEN_DOUBLE_QUOTE || root->type == TOKEN_SINGLE_QUOTE
			|| root->type == TOKEN_WORD || root->type == TOKEN_VARIABLE))
		return (create_status_signal(handle_exec_command(root, shell_state)));
	if (root->type == TOKEN_PIPE)
		return (execute_pipe(root->left, root->right, shell_state));
	else if (root->type == TOKEN_SUBSHELL)
		execute_subshell(root, shell_state);
	else if (root->type == TOKEN_AND)
		execute_and(root->left, root->right, shell_state);
	else if (root->type == TOKEN_OR)
		execute_or(root->left, root->right, shell_state);
	else if (root->type == TOKEN_REDIRECT_OUTPUT
		|| root->type == TOKEN_REDIRECT_APPEND
		|| root->type == TOKEN_REDIRECT_INPUT
		|| root->type == TOKEN_HEREDOC)
		handle_exec_redirection(root, shell_state);
	return (0);
}

/* // Fonction pour parcourir l'AST et exécuter les commandes
int	execute_ast(t_ast_node *root, t_shell_state *shell_state)
{
	int		status;
	char	**args;

	status = 0;
	if (!root)
		return (0);
	if (root->type == TOKEN_ASSIGNMENT)
	{
		args = build_args(&root, shell_state);
		if (root->right->type == TOKEN_DOUBLE_QUOTE)
			args = build_args(&root->right->right, shell_state);
		else		
		{
			while (root != NULL && root->type == TOKEN_ASSIGNMENT)
			{

				update_set(shell_state, root->left->value, root->right->value);
				root = root->next;
			}
			if (root != NULL && root->type == TOKEN_WORD)
				execute_ast(root, shell_state);
		}
		free_args(args);
		return (0);
	}
	else if (root->type == TOKEN_WORD || root->type == TOKEN_VARIABLE)
	{
		args = build_args(&root, shell_state);
		status = execute_command(root->value, args, shell_state);
		char *exit_status;
		exit_status = ft_itoa(status);
		update_set(shell_state, "?", exit_status);
		free(exit_status);
		restore_fds(shell_state);
		free_args(args);
		return (status);
	}
	else if (root->type == TOKEN_PIPE)
	{
		execute_pipe(root->left, root->right, shell_state);
	//	printf("TOKEN_PIPE \n");
		restore_fds(shell_state);
	}
	else if (root->type == TOKEN_SUBSHELL)
	{
		execute_subshell(root, shell_state);
	}
	else if (root->type == TOKEN_AND)
	{
		execute_and(root->left, root->right, shell_state);
	}
	else if (root->type == TOKEN_OR)
	{
		execute_or(root->left, root->right, shell_state);
	}
	else if (root->type == TOKEN_REDIRECT_OUTPUT)
	{
		//save_fds(shell_state);
		redirect_output_to_file(root->right->value);
		execute_ast(root->left, shell_state);
	//	printf("TOKEN_REDIRECT_OUTPUT \n");
		restore_fds(shell_state);
	}
	else if (root->type == TOKEN_REDIRECT_APPEND)
	{
		//save_fds(shell_state);
		redirect_append_output_to_file(root->right->value);
		execute_ast(root->left, shell_state);
	//	printf("TOKEN_REDIRECT_APPEND \n");
		restore_fds(shell_state);
	}
	else if (root->type == TOKEN_REDIRECT_INPUT)
	{
		//save_fds(shell_state);
		redirect_input_from_file(root->right->value);
		execute_ast(root->left, shell_state);
	//	printf("TOKEN_REDIRECT_INPUT \n");
		restore_fds(shell_state);
	}
	else if (root->type == TOKEN_HEREDOC)
	{
		//save_fds(shell_state);
		heredoc_input(root->right->value);
		execute_ast(root->left, shell_state);
	//	printf("TOKEN_HEREDOC \n");
		restore_fds(shell_state);
	}
	return (0);
} */
