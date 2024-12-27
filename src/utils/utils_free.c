/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 04:53:17 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/10 04:53:38 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(int nb, ...)
{
	va_list	ap;
	void	*ptr;

	va_start(ap, nb);
	while (nb--)
	{
		ptr = va_arg(ap, void *);
		free(ptr);
	}
	va_end(ap);
}
