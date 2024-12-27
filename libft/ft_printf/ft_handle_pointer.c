/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:32:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/08 10:07:04 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Fonction pour convertir une adresse de pointeur
  en chaîne de caractères hexadécimale
*/
void	pointer_to_hex_str(void *ptr, char *str)
{
	unsigned long long	value;
	char				*ptr1;
	char				*ptr2;
	char				tmp_char;
	unsigned long long	tmp_value;

	value = (unsigned long long)ptr;
	ptr1 = str;
	ptr2 = str;
	while (value > 0)
	{
		tmp_value = value;
		*ptr1++ = (char) "0123456789abcdef"[tmp_value % 16];
		value /= 16;
	}
	*ptr1++ = 'x';
	*ptr1++ = '0';
	*ptr1-- = '\0';
	while (ptr2 < ptr1)
	{
		tmp_char = *ptr1;
		*ptr1-- = *ptr2;
		*ptr2++ = tmp_char;
	}
}

void	handle_pointer(t_formatSpec *fs, va_list args)
{
	void	*value;
	char	buffer[50];
	int		len;

	value = va_arg(args, void *);
	if (value != NULL)
		pointer_to_hex_str(value, buffer);
	else
		ft_strlcpy (buffer, "(nil)", 6);
	len = ft_strlen(buffer);
	if (!fs->left_align)
	{
		if ((fs->width - len) > 0)
			fs->count = fs->count + fs->width - len;
		print_padding(fs->width - len, ' ');
	}
	fs->count = fs->count + ft_strlen(buffer);
	ft_putstr_fd(buffer, 1);
	if (fs->left_align)
	{
		if ((fs->width - len) > 0)
			fs->count = fs->count + fs->width - len;
		print_padding(fs->width - len, ' ');
	}
}
