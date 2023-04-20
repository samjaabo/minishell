/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/19 22:06:21 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	g_data;

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
	if (line && line[0] && isatty(STDIN_FILENO))
		add_history(line);
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
		//printf("status->(%d)\n", g_data.exit_status);
		g_data.status = STATUS_READIND;
		rl_catch_signals = 0;
		if (g_data.succ_str && g_data.fail_str)
			str = prompt(g_data.exit_status, g_data.succ_str, g_data.fail_str);
		else
			str = prompt(g_data.exit_status, "minshell: ", "minshell: ");
		if (!str)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
		{
			//add_history(str);
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
				// while (lst)
				// {
				// 	printf("ARGS:\n");
				// 	i = 0;
				// 	while (lst->args && lst->args[i])
				// 		printf("%s\n", lst->args[i++]);
				// 	printf("\nREDIRS:\n");
				// 	i = 0;
				// 	while (lst->redirs && lst->redirs[i] && lst->types[i])
				// 	{
				// 		printf("%s\ttype: %s\n", lst->redirs[i], lst->types[i]);
				// 		i++;
				// 	}
				// 	printf("\n");
				// 	lst = lst->next;
				// }
				// ft_lstclear(&lst);
			}
		}
		free(str);
	}
	ft_exit();
	return (0);
}
