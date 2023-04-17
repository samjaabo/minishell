/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:55:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/17 19:01:10 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_pipe_in_parent(t_cmd *cmd)
{
	int	fd[2];

	if (!cmd->next)
		return (SUCCESS);
	if (pipe(fd) < 0)
		return (ft_perror("pipe 14 syscall") ,ERROR);
	g_data.pipe_old = g_data.pipe_in;
	g_data.pipe_in = fd[0];
	g_data.pipe_out = fd[1];
	cmd->pipe_out = fd[1];
	cmd->next->pipe_in = fd[0];
	if (cmd->id == 0)
		cmd->pipe_in = fd[0];
	//cmd->pipe_in;
	return (SUCCESS);
}

int	ft_pipe_in_child(t_cmd *cmd)
{
	if (cmd->id != 0 && cmd->next)//commands in center
	{
		if (dup2(cmd->pipe_in, STDIN_FILENO) < 0)
			return (ft_perror("dup2 006 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close 01 syscall"), ERROR);
		if (dup2(cmd->pipe_out, STDOUT_FILENO) < 0)
			return (ft_perror("dup2 02 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_out) < 0)
			return (ft_perror("close2  03 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->next->pipe_in) < 0)
			return (ft_perror("close2  03 syscall"), ERROR);
	}
	if (cmd->id != 0 && !cmd->next)//last command
	{
		if (dup2(cmd->pipe_in, STDIN_FILENO) < 0)
			return (ft_perror("dup2 04 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close2 04 syscall"), ERROR);
	}
	if (cmd->id == 0 && cmd->next)//first command
	{
		if (dup2(cmd->pipe_out, STDOUT_FILENO) < 0)
			return (ft_perror("dup2 04 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_out) < 0)
			return (ft_perror("close2 04 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close2 04 syscall"), ERROR);
	}
	
	return (SUCCESS);
}

int	ft_close_pipe_in_parent(t_cmd *cmd)
{
	//dprintf(2, "parent id=%d", cmd->id);
	if (cmd->id != 0 && cmd->next)
	{
		if (close(cmd->pipe_in) < 0)
			return (ft_perror("close 5564 syscall"), ERROR);
		g_data.pipe_old = -42;
	}
	if (cmd->next)
	{
		if (close(cmd->pipe_out) < 0)
			return (ft_perror("close 559 syscall"), ERROR);
	}
	if (!cmd->next && cmd->id != 0)
	{
		if (close(cmd->pipe_in) < 0)
			return (ft_perror("close 904 syscall"), ERROR);
	}
	return (SUCCESS);
}