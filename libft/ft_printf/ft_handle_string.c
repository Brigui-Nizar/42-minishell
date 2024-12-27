/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 08:40:43 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/12 17:35:08 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size_parse_str(t_formatSpec *fs, int strlen)
{
	int	temp;
	int	count;

	temp = 0;
	count = strlen;
	if (fs->add_hash && strlen > 0)
		count += 2;
	if (fs->add_space)
		count += 1;
	if (fs->add_plus && strlen > 0)
		count ++;
	temp = ft_max (fs->precision, fs->width);
	count += ft_max (temp, strlen);
	return (count);
}

/*
truncate whith precision (%.10s)
*/
static void	precision(t_formatSpec *fs, char *dest)
{
	if (fs->precision > 0 && (int)ft_strlen (dest) > fs->precision)
	{
		ft_memset (dest + fs->precision, 0,
			(int) ft_strlen (dest) - fs->precision);
	}
	if (fs->precision == 0)
		ft_memset (dest, 0, (int) ft_strlen (dest) - fs->precision);
}

char	*set_src_is_null(t_formatSpec *fs, char *null_string, int *strlen)
{
	*strlen = ft_strlen (null_string);
	if (fs->precision >= 0 && fs->precision < 6)
	{
		*strlen = ft_strlen (null_string);
		null_string = "";
	}
	return (null_string);
}

static char	*set_dest_str(t_formatSpec *fs, char *str)
{
	int		strlen;
	char	*null_string;
	char	*dest;

	strlen = 0;
	null_string = "(null)";
	if (str == NULL)
		null_string = set_src_is_null(fs, null_string, &strlen);
	else
		strlen = ft_strlen (str);
	dest = ft_calloc (get_size_parse_str (fs, strlen) + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	if (str == NULL)
		dest = ft_memcpy (dest, null_string, ft_strlen(null_string));
	else
		dest = ft_memcpy (dest, str, ft_strlen(str));
	if (dest == NULL)
		return (NULL);
	return (dest);
}

void	handle_string(t_formatSpec *fs, va_list args)
{
	char	*str;
	char	*dest;

	str = va_arg(args, char *);
	dest = set_dest_str(fs, str);
	if (!dest)
		return ;
	precision (fs, dest);
	add_space_before (fs, dest, ' ');
	add_space_after (fs, dest);
	write (1, dest, ft_strlen (dest));
	fs->count += ft_strlen (dest);
	free(dest);
}
