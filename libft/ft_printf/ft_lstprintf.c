/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:12:19 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/06 19:39:01 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_formatHandler	*ft_lstprintf_new(char *specifier, t_ft_format_handler handler)
{
	t_formatHandler	*list;

	list = ft_calloc (1, sizeof(t_formatHandler));
	if (list == NULL)
		return (NULL);
	list->specifier = ft_strdup(specifier);
	list->handler = handler;
	list->next = NULL;
	return (list);
}

void	ft_lstprintf_add_back(t_formatHandler **lst, t_formatHandler *new)
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

void	ft_lstprintf_clear(t_formatHandler **lst, void (*del)(void *))
{
	t_formatHandler	*liste;
	t_formatHandler	*tmp;

	tmp = *lst;
	while (tmp)
	{
		liste = tmp;
		del(liste->specifier);
		tmp = tmp->next;
		free(liste);
	}
	*lst = NULL;
}
