/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:53:06 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 09:42:55 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*liste;

	i = 0;
	liste = lst;
	while (liste != NULL)
	{
		liste = liste->next;
		i++;
	}
	return (i);
}
