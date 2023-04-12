/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:23:42 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/12 16:40:16 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data g_data;

static void	ft_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_data.status == STATUS_READIND)
	{
		rl_replace_line("", 0);
		if (g_data.control == 0)
		{
			rl_on_new_line();
			rl_redisplay();
			write(1, "\n", 1);
		}
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_data.status == STATUS_HERE_DOC)
	{
		g_data.here_doc_control_c = TRUE;
		g_data.control = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		close(0);
	}
	else if (g_data.status == STATUS_EXECUTING)
		write(1, "\n", 1);
}

void	ft_control_slash(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_data.status == STATUS_EXECUTING)
	{
		exit(1);
	}
}

void	ft_control_d(void)
{
	rl_replace_line("", 0);
	rl_clear_history();
    // rl_on_new_line();
    // rl_redisplay();
	write(1, "exit\n", 5);
	ft_exit();
}

int	ft_signals(void)
{
	if (signal(SIGINT, ft_control_c) == SIG_ERR)
		return(ft_error("signal function","fail to set signal handler\n"), ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return(ft_error("signal function","fail to set signal handler\n"), ERROR);
	return (SUCCESS);
}