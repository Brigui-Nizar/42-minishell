/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:58:01 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/09 04:45:48 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "structure.h"

void	free_split(char **args);
void	free_env(char **env);
void	lst_clear_env(t_env_var *env);
void	free_minishell_loop(t_shell_state *shell_state);
char	*ft_strjoin_free_s1_s2(char *s1, char *s2);

#endif
