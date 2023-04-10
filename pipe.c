/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:55:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/10 18:20:30 by samjaabo         ###   ########.fr       */
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
	return (SUCCESS);
}

int	ft_pipe_in_child(t_cmd *cmd)
{
	if (cmd->id != 0 && cmd->next)
	{
		if (dup2(g_data.pipe_old, STDIN_FILENO) < 0)
			return (ft_perror("dup2 006 syscall"), ERROR);
		if (close(g_data.pipe_old) < 0)
			return (ft_perror("close 01 syscall"), ERROR);
	}
	if (cmd->id != 0 && !cmd->next)
	{
		if (dup2(g_data.pipe_in, STDIN_FILENO) < 0)
			return (ft_perror("dup2 0x06 syscall"), ERROR);
		if (close(g_data.pipe_in) < 0)
			return (ft_perror("close 0x1 syscall"), ERROR);
	}
	if (cmd->next)
	{
		if (dup2(g_data.pipe_out, STDOUT_FILENO) < 0)
			return (ft_perror("dup2 02 syscall"), ERROR);
		if (close(g_data.pipe_out) < 0)
			return (ft_perror("close2  03 syscall"), ERROR);
	}
	if (cmd->id == 0 && cmd->next && close(g_data.pipe_in) < 0)
			return (ft_perror("close2 04 syscall"), ERROR);
	return (SUCCESS);
}

int	ft_close_pipe_in_parent(t_cmd *cmd)
{
	if (cmd->id != 0 && cmd->next)
	{
		if (close(g_data.pipe_old) < 0)
			return (ft_perror("close 5564 syscall"), ERROR);
		g_data.pipe_old = -42;
	}
	if (cmd->next)
	{
		if (close(g_data.pipe_out) < 0)
			return (ft_perror("close 559 syscall"), ERROR);
	}
	if (!cmd->next && cmd->id != 0)
	{
		if (close(g_data.pipe_in) < 0)
			return (ft_perror("close 904 syscall"), ERROR);
	}
	return (SUCCESS);
}