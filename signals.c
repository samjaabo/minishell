/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:23:42 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/10 22:15:53 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_data.status == STATUS_READIND)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_data.status == STATUS_HERE_DOC)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
	}
}

static void	ft_control_slash(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_data.status == STATUS_READIND || g_data.status == STATUS_HERE_DOC)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_control_d(void)
{
	rl_clear_history();
    rl_on_new_line();
    rl_redisplay();
	write(1, "exit\n", 5);
	ft_exit();
}

int	ft_signals(void)
{
	if (signal(SIGINT, ft_control_c) == SIG_ERR)
		return(ft_error("signal function","fail to set signal handler\n"), ERROR);
	if (signal(SIGQUIT, ft_control_slash) == SIG_ERR)
		return(ft_error("signal function","fail to set signal handler\n"), ERROR);
	return (SUCCESS);
}