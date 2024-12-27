/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:32:20 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/18 16:10:39 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Fonction pour convertir une adresse de pointeur
  en chaîne de caractères hexadécimale
*/
static void	add_char(char *dest, char c, int count)
{
	int	len;
	int	i;

	len = ft_strlen(dest);
	i = 0;
	while (i < count)
	{
		dest[len + i] = c;
		i++;
	}
	dest[len + count] = '\0';
}

static void	add_zero(t_formatSpec *fs, char *dest, char flag)
{
	size_t	diff;
	int		len;
	int		sign;

	sign = 0;
	len = ft_strlen (dest);
	if (fs->add_hash == 1)
		sign = 2;
	if (fs->add_space == 1)
		sign ++;
	if (fs->pad_zero > 0 && fs->width - sign > len)
	{
		diff = fs->width - sign - ft_strlen(dest);
		ft_memmove(dest + diff, dest, len + 1);
		ft_memset(dest, flag, diff);
	}
}

static void	add_precision(t_formatSpec *fs, char *dest, int len)
{
	int		diff;
	char	flag;

	flag = '0';
	if (fs->precision > len)
	{
		diff = fs->precision - len;
		ft_memmove(dest + diff, dest, len + 1);
		ft_memset(dest, flag, diff);
	}
	if (fs->precision != -1)
		flag = ' ';
	if (fs->pad_zero || fs->add_space)
		add_zero (fs, dest, flag);
}

static void	add_padding(t_formatSpec *fs, char *dest, int len)
{
	int		diff;
	char	fill_char;

	if (fs->width > len)
	{
		diff = fs->width - len;
		if (fs->pad_zero && fs->precision < 0)
			fill_char = '0';
		else
			fill_char = ' ';
		if (fs->left_align)
		{
			add_char(dest, ' ', diff);
		}
		else
		{
			ft_memmove(dest + diff, dest, len + 1);
			ft_memset(dest, fill_char, diff);
		}
	}
}

void	handle_hexa(t_formatSpec *fs, va_list args)
{
	unsigned int	value;
	int				strlen;
	int				total_size;
	char			*dest;
	int				len;

	value = va_arg (args, unsigned int);
	strlen = size_in_base (value, "0123456789abcdef");
	total_size = get_size_hexa(fs, strlen);
	dest = (char *) ft_calloc(total_size + 1, sizeof(char));
	if (dest == NULL)
		return ;
	if (fs->precision != 0 && value == 0)
		dest[0] = '0';
	else
		base_to_str(value, dest + strlen - 1, "0123456789abcdef");
	add_precision(fs, dest, strlen);
	if (fs->add_hash && value != 0)
		add_prefix(dest, value, "0x");
	len = ft_strlen(dest);
	add_padding(fs, dest, len);
	write(1, dest, ft_strlen(dest));
	fs->count += ft_strlen(dest);
	free(dest);
}
