/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(int exit_status, char *succ, char *fail)
{
	static char	*line = NULL;

	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDOUT_FILENO))
		{
			if (exit_status == 0)
				line = readline(succ);
			else
				line = readline(fail);
		}
		else
			line = readline("");
	}
	else
		line = ft_read();
	if (!line)
		ft_control_d();
	return (line);
}

/*----------------------------------------------------------------*/

static void	ft_do_loop(char *str)
{
	t_cmd		*lst;
	char		**splited;

	if (str[0] != '\0')
	{
		if (isatty(STDIN_FILENO))
			add_history(str);
		splited = syntax_and_split(str);
		if (splited)
		{
			g_data.status = STATUS_EXECUTING;
			lst = process_data(splited);
			if (ft_getenv("PATH") >= 0)
				ft_exec(lst, g_data.env[ft_getenv("PATH")] + 5);
			else
				ft_exec(lst, NULL);
			ftx_lstclear(&lst);
		}
	}
	free(str);
}

/*----------------------------------------------------------------*/

int	main(int ac, char **av, char **env)
{
	char		*line;

	(void)ac;
	(void)av;
	ft_init(env);
	ft_signals();
	while (TRUE)
	{
		g_data.status = STATUS_READIND;
		rl_catch_signals = 0;
		if (g_data.succ_str && g_data.fail_str)
			line = prompt(g_data.exit_status, g_data.succ_str, g_data.fail_str);
		else
			line = prompt(g_data.exit_status, "minshell: ", "minshell: ");
		ft_do_loop(line);
	}
	ft_exit();
	return (0);
}
