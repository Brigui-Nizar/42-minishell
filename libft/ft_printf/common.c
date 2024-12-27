/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:49:09 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/12 17:46:49 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
Fonction pour afficher un nombre d'espaces ou de zéros
*/
void	print_padding(int count, char pad_char)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putchar_fd(pad_char, 1);
		i++;
	}
}

void	add_blank(t_formatSpec *fs, char *dest)
{
	int	len;

	len = ft_strlen(dest);
	if (fs->add_space > 0)
	{
		ft_memmove(dest + 1, dest, len + 1);
		ft_memset(dest, ' ', 1);
	}
}

void	add_space_before(t_formatSpec *fs, char *dest, int flag_precision)
{
	size_t	diff;
	int		len;

	len = ft_strlen(dest);
	if (fs->width > len && !fs->left_align)
	{
		diff = fs->width - ft_strlen(dest);
		ft_memmove(dest + diff, dest, len + 1);
		ft_memset(dest, flag_precision, diff);
	}
}

void	add_space_after(t_formatSpec *fs, char *dest)
{
	size_t	diff;
	int		len;

	len = ft_strlen(dest);
	if (fs->width > len && fs->left_align)
	{
		diff = fs->width - ft_strlen(dest);
		ft_memset(dest + len, ' ', diff);
	}
}

void	add_prefix(char *dest, unsigned int value, char *prefix)
{
	if (value != 0)
	{
		ft_memmove(dest + ft_strlen(prefix), dest, ft_strlen(dest) + 1);
		ft_memcpy(dest, prefix, ft_strlen(prefix));
	}
}
