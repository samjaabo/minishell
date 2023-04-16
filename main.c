/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/16 17:12:31 by samjaabo         ###   ########.fr       */
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
    while (TRUE)
    {
		dprintf(2, "status = (%d)\n", g_data.exit_status);
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
		cmd = body(line);
		ft_exec(cmd, g_data.env[ft_getenv("PATH")]);
		ftx_lstclear(&cmd);
    }
	ft_exit();
}

