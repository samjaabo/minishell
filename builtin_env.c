/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **args)
{
	int	i;

	if (args[1])
		return (ft_error("env", "takes no argument"));
	i = 0;
	while (g_data.env && g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "_=", 2))
		{
			printf("_=/usr/bin/env\n");
			++i;
			continue ;
		}
		if (!ft_strncmp(g_data.env[i], "PATH=", 5) && g_data.default_path)
			;
		else if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
		++i;
	}
	g_data.exit_status = SUCCESS;
}

int	ft_is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (FALSE);
	if (cmd->id == 0 && cmd->next)
		return (FALSE);
	if (cmd->id != 0)
		return (FALSE);
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (TRUE);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		return (TRUE);
	return (FALSE);
}

int	ft_exec_builtins(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		ft_cd(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "echo", 5))
		ft_echo(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "env", 4))
		ft_env(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		ft_export(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd(0);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd->args);
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_builtin_exit(cmd->args, &cmd);
	else
		return (FALSE);
	return (TRUE);
}

int	ft_builtins(t_cmd *cmd)
{
	if (cmd->args)
		ft_update_lastcmd(cmd->args);
	if (!ft_is_builtin(cmd))
		return (SUCCESS);
	if (ft_pipe_in_child(cmd) == ERROR)
		return (ERROR);
	if (ft_close_pipe_in_parent(cmd) == ERROR)
		return (ERROR);
	if (ft_redirection(cmd) == ERROR)
		return (ERROR);
	ft_exec_builtins(cmd);
	return (SUCCESS);
}

int	ft_copy_env(char **env)
{
	int		i;
	char	**arr;

	i = 0;
	while (env && env[i])
	{
		arr = ft_realloc(g_data.env, ft_strdup(env[i]));
		if (!arr)
			return (ft_clear(g_data.env), g_data.env = NULL, ERROR);
		g_data.env = arr;
		++i;
	}
	return (SUCCESS);
}
