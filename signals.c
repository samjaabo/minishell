/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:23:42 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_control_c(int sig)
{
	if (sig != SIGINT)
		return ;
	if (g_data.status == STATUS_READIND)
	{
		g_data.exit_status = 1;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_data.status == STATUS_HERE_DOC)
	{
		g_data.exit_status = 1;
		g_data.here_doc_control_c = TRUE;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		close(0);
	}
}

void	ft_control_slash(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_data.status == STATUS_EXECUTING)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	ft_control_d(void)
{
	rl_replace_line("", 0);
	rl_clear_history();
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 6);
	ft_exit();
}

int	ft_signals(void)
{
	if (signal(SIGINT, ft_control_c) == SIG_ERR)
		return (ft_error("signal function",
				"fail to set signal handler for SIGINT\n"), ERROR);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ft_error("signal function",
				"fail to set signal handler for SIGQUIT\n"), ERROR);
	return (SUCCESS);
}

void	ft_print_signal(void)
{
	int	sig;

	sig = g_data.exit_status - 128;
	if (sig == SIGHUP)
		printf("Hangup: 1\n");
	else if (sig == SIGILL)
		printf("Illegal instruction: 4\n");
	else if (sig == SIGTRAP)
		printf("Trace/BPT trap: 5\n");
	else if (sig == SIGTERM)
		printf("Terminated: 15\n");
	else if (sig == SIGSEGV)
		printf("Segmentation fault: 11\n");
	else if (sig == SIGKILL)
		printf("Killed: 9\n");
	else if (sig == SIGABRT)
		printf("Abort trap: 6\n");
	else if (sig == SIGFPE)
		printf("Floating point exception: 8\n");
	else if (sig == SIGXCPU)
		printf("Cputime limit exceeded: 24\n");
	else if (sig == SIGBUS)
		printf("Bus error: 10\n");
}
