/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrigui <nbrigui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:52:42 by nbrigui           #+#    #+#             */
/*   Updated: 2024/08/27 17:41:25 by nbrigui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	This function displays the minishell banner
	if the number of arguments is greater than 1
*/
void	diplays_minishell_banner(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		printf(RED BOLD "**************************************\n" RESET);
		printf(RED BOLD "***********                 **********\n" RESET);
		printf(RED BOLD "***********    MINISHELL    **********\n" RESET);
		printf(RED BOLD "***********                 **********\n" RESET);
		printf(RED BOLD "**************************************\n\n" RESET);
	}
}
