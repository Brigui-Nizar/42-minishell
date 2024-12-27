/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 07:19:40 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 09:59:30 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*liste;
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		liste = tmp;
		del(liste->content);
		tmp = tmp->next;
		free(liste);
	}
	*lst = NULL;
}
