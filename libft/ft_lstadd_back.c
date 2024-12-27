/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 05:29:46 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 09:40:10 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*liste;

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
