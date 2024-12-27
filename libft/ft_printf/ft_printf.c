/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:39:29 by nbrigui           #+#    #+#             */
/*   Updated: 2024/06/14 14:44:31 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Fonction pour convertir un entier en chaîne de caractères
 */
void	init_format_handlers(t_formatHandler *handlers)
{
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("s", handle_string));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("p", handle_pointer));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("d", handle_decimal));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("i", handle_int));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("u", handle_unsigned));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("C", handle_char));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("x", handle_hexa));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("X", handle_hexa_upper));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("o", handle_octal));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("hhd", handle_int));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("%", handle_percent));
	ft_lstprintf_add_back(&handlers, ft_lstprintf_new("", handle_void));
}

int	start(const char **p, t_formatSpec *fs, t_formatHandler *handlers,
	va_list args)
{
	while (**p != '\0')
	{
		if (**p == '%' && (p[0][1]) != '\0')
		{
			(*p)++;
			parse_format_specifiers(p, fs, handlers, args);
			continue ;
		}
		if (**p == '\0')
			break ;
		if (**p != '\0')
		{
			ft_putchar_fd(**p, 1);
			fs->count = fs->count + 1 ;
		}
		(*p)++;
	}
	return (fs->count);
}

static t_formatSpec	*ft_init_fs(t_formatSpec *fs)
{
	fs->add_plus = -1;
	fs->add_space = -1;
	fs->add_hash = 0;
	fs->pad_zero = 0;
	fs->left_align = 0;
	fs->width = 0;
	fs->precision = -1;
	fs->count = 0;
	return (fs);
}

static void	free_all(t_formatHandler *handlers, t_formatSpec *fs)
{
	ft_lstprintf_clear(&handlers, free);
	free(handlers);
	free(fs->tmp);
	free(fs);
}

int	ft_printf(const char *arg0, ...)
{
	t_formatHandler	*handlers;
	const char		*p;
	va_list			args;
	t_formatSpec	*fs;
	int				count;

	if (arg0 == NULL)
		return (-1);
	fs = malloc(sizeof(*fs));
	if (fs == NULL)
		return (0);
	ft_init_fs(fs);
	handlers = ft_lstprintf_new ("c", handle_char);
	init_format_handlers(handlers);
	va_start(args, arg0);
	p = ft_calloc (ft_strlen (arg0) + 2, sizeof(char));
	if (p == NULL)
		return (0);
	ft_strlcpy ((char *)p, arg0, ft_strlen (arg0) + 1);
	fs->tmp = (char *)p;
	start(&p, fs, handlers, args);
	va_end(args);
	count = fs->count;
	free_all(handlers, fs);
	return (count);
}

/*
base flag : 
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.

bonus : combinaison :
 %3d Une donnée entière de type int. 
 Si la valeur est inférieure à 100, 
 des caractères blancs sont ajoutés pour compléter sur 3 caractères.
    ex : ft_printf("%3d", 1) -> $__1 (2 espace)
 %03d Une donnée entière de type int.
  Si la valeur est inférieure à 100,
  des caractères 0 sont ajoutés pour compléter sur 3 caractères.
 ex : ft_printf("%03d", 1) -> $001
 %+d Une donnée entière de type int.
  ajoute le signe
 ex : ft_printf("%+d", 42) -> $+42

 %10s Une donnée de type chaîne de caractères
  sur 10 caractères alignés par la droite.
  ex : ft_printf("%10s", "a") -> $_________a (9 espace)
 %-10s Une donnée de type chaîne de caractères
  sur 10 caractères alignés par la gauche. (justifier a droite)
  ex : ft_printf("%-10s", "a") -> $a_________ (9 espace apres)

%.5s Une donnée de type chaîne de caractères
 tronque de 5 caractere maximum
 ex :ft_printf(":%.5s!", "HelloWorld");-> $:Hello!

% s Une donnée de type chaîne de caractères
avec un espace avent
 ex :ft_printf(":% s!", "HelloWorld");-> $:_HelloWorld! (1 espace)

 %x une donnee hexadecimal 
 ex :ft_printf("%x", p);-> $a01122fe

 %#x une donnee hexadecimal
  prefixer par 0x
 ex :ft_printf("%#x", p);-> $0xa01122fe
 ** L'indicateur # ne doit pas être utilisé 
 avec les types c, lc, d, i, u ou s
*/