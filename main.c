/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 19:01:26 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	main(int ac, char **av, char **env)
{
	t_cmd		*lst;
	char		*str;
	char		**splited;

	(void)ac;
	(void)av;
	ft_init(env);
	if (ft_signals() < 0)
		return (1);
	while (1)
	{
		printf("status->(%d)\n", g_data.exit_status);
		g_data.status = STATUS_READIND;
		rl_catch_signals = 0;
		if (g_data.succ_str && g_data.fail_str)
			str = prompt(g_data.exit_status, g_data.succ_str, g_data.fail_str);
		else
			str = prompt(g_data.exit_status, "minshell: ", "minshell: ");
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
	ft_exit();
	return (0);
}
