/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:00:02 by nbrigui           #+#    #+#             */
/*   Updated: 2024/09/22 16:48:28 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function creates a new node
	and initializes it with the specifier
	and the handler
*/
t_formatHandler	*ft_lst_builtins_new(char *specifier, t_ft_cmd_handler handler)
{
	t_formatHandler	*list;

	list = ft_calloc (1, sizeof(t_formatHandler));
	if (list == NULL)
		return (NULL);
	list->cmd = ft_strdup(specifier);
	list->handler = handler;
	list->next = NULL;
	return (list);
}

/*
	This function adds a new node at the end of the list
*/
void	ft_lst_builtins_add_back(t_formatHandler **lst, t_formatHandler *new)
{
	t_formatHandler	*liste;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	liste = *lst;
	while (liste && liste->next != NULL)
	{
		liste = liste->next;
	}
	liste->next = new;
}

/*
	@TODO
*/
void	ft_lst_builtins_clear(t_formatHandler **lst, void (*del)(void *))
{
	t_formatHandler	*liste;
	t_formatHandler	*tmp;

	tmp = *lst;
	while (tmp)
	{
		liste = tmp;
		del(liste->cmd);
		tmp = tmp->next;
		free(liste);
	}
	*lst = NULL;
}
