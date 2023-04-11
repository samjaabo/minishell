/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/11 18:30:27 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int main(int i, char **v)
{
    char	*line;
	t_cmd  *cmd;

	(void)v;
	(void)i;
	ft_init();
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
		line = prompt(g_data.exit_status, g_data.succ_str, g_data.fail_str);
		g_data.status = STATUS_EXECUTING;
		if (!ft_strncmp(line, "exit", 5))
			ft_exit();
		cmd = body(line);
		ft_exec(cmd, getenv("PATH"), NULL);
		ftx_lstclear(&cmd);
    }
	ft_exit();
}

