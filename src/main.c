/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 03:04:47 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/17 13:48:11 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	is_unexpected_token(const char *line);
void	close_fds(t_shell_state *shell_state);

int	get_exit_status_code(t_shell_state *shell_state)
{
	t_env_var	*exit_status;

	exit_status = find_env_var(shell_state->env_vars, "?");
	if (exit_status)
		return (ft_atoi(exit_status->value));
	return (0);
}

void	free_minishell(t_shell_state *shell_state)
{
	free_minishell_loop(shell_state);
	free(shell_state->minishell_path);
	ft_lst_builtins_clear(&shell_state->handlers, free);
	lst_clear_env(shell_state->tmp_env_vars);
}

/*
	mode non interactif
	Exemple: ./minishell -c "ls -l | grep foo && echo bar || echo boo"
*/
void	minishell_bash(int argc, char **argv,
	t_shell_state *shell_state)
{
	int				status;

	if (argc > 1 && ft_strnstr(argv[1], "-c", 2) != NULL)
	{
		sinal_handler_main();
		shell_state->input = ft_strdup(argv[2]);
		if (is_unexpected_input(shell_state)
			|| !is_valid_input(shell_state->input, shell_state))
		{
			status = get_exit_status_code(shell_state);
			free_minishell(shell_state);
			exit(status);
		}
		restore_fds(shell_state);
		lexer(shell_state->input, shell_state);
		shell_state->ast_root = parser(&shell_state->tokens, 0);
		execute_ast(shell_state->ast_root, shell_state);
		status = get_exit_status_code(shell_state);
		close_fds(shell_state);
		free_minishell(shell_state);
		exit(status);
	}
}

void	main_loop(t_shell_state *shell_state)
{
	if (is_valid_input(shell_state->input, shell_state))
	{
		add_history(shell_state->input);
		lexer(shell_state->input, shell_state);
		shell_state->ast_root = parser(&shell_state->tokens, 0);
		execute_ast(shell_state->ast_root, shell_state);
		restore_fds(shell_state);
		signal_main_print_message();
		free_minishell_loop(shell_state);
		close_fds(shell_state);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	shell_state;

	init_minishell(&shell_state, envp);
	minishell_bash(argc, argv, &shell_state);
	while (1)
	{
		sinal_handler_main();
		update_prompt(&shell_state);
		free_minishell_loop(&shell_state);
		shell_state.input = readline(shell_state.prompt);
		main_signal_set_exit_status(&shell_state);
		if (is_unexpected_input(&shell_state))
			continue ;
		main_loop(&shell_state);
	}
	return (0);
}
