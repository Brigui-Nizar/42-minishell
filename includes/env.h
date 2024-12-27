/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:18:03 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/23 05:50:53 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "structure.h"

/* */
char		*get_key(char *env_entry);
char		*get_value(char *env_entry);

t_env_var	*find_env_var(t_env_var *head, const char *name);
void		set_env_var(t_env_var **head, const char *name, const char *value,
				int is_exported);

char		**env_list_to_array(t_env_var *head);
char		**set_list_to_array(t_env_var *head);

char		*concat_env_var(const char *name, const char *value);

#endif