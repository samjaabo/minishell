/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/13 20:01:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data	g_data;

void	ft_env()
{
	int i;

	i = 0;
	while (g_data.env && g_data.env[i])
	{
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
		++i;
	}
	g_data.exit_status = 0;
}

int	ft_builtins(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (SUCCESS);
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd->args[1]);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd->args);
	else
		return (SUCCESS);
	printf("BUILTIN\n");
	return (IS_BUILTIN);
}
