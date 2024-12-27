/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorres <rtorres@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:47:17 by nbrigui           #+#    #+#             */
/*   Updated: 2024/10/14 13:49:16 by rtorres          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sinal_handler_main(void);
void	sinal_handler_fork(void);
void	sinal_handler_heredoc(void);
void	signal_main_print_message(void);
void	main_signal_set_exit_status(t_shell_state *shell_state);

#endif