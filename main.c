/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/14 13:49:39 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	g_data;

int main(int argc, char **argv, char **env)
{
    char	*line;
	t_cmd  *cmd;

	(void)argc;
	(void)argv;
	ft_init(env);
	if (ft_signals() < 0)
		return (1);
    while (1)
    {
		g_data.status = STATUS_READIND;
		// if (read(0, 0, 0) < 0)
		// {
		// 	ft_perror("can't read from STDIN");
		// 	break ;
		// }
		if (g_data.succ_str && g_data.fail_str)
			line = prompt(g_data.exit_status, g_data.succ_str, g_data.fail_str);
		else
			line = prompt(g_data.exit_status, "minshell: ", "minshell: ");
		g_data.status = STATUS_EXECUTING;
		if (!ft_strncmp(line, "exit", 5))
			ft_exit();
		cmd = body(line);
		ft_exec(cmd, getenv("PATH"), NULL);
		ftx_lstclear(&cmd);
    }
	ft_exit();
}

