/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:55:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_in_parent(t_cmd *cmd)
{
	int	fd[2];

	if (!cmd->next)
		return (SUCCESS);
	if (pipe(fd) < 0)
		return (ft_perror("pipe syscall"), ERROR);
	cmd->pipe_out = fd[1];
	cmd->next->pipe_in = fd[0];
	if (cmd->id == 0)
		cmd->pipe_in = fd[0];
	return (SUCCESS);
}

static int	ft_middle_pipe_cmds(t_cmd *cmd)
{
	if (cmd->id != 0 && cmd->next)
	{
		if (dup2(cmd->pipe_in, STDIN_FILENO) < 0)
			return (ft_perror("dup2 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close syscall"), ERROR);
		if (dup2(cmd->pipe_out, STDOUT_FILENO) < 0)
			return (ft_perror("dup2 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_out) < 0)
			return (ft_perror("close2  syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->next->pipe_in) < 0)
			return (ft_perror("close2 syscall"), ERROR);
	}
	return (SUCCESS);
}

int	ft_pipe_in_child(t_cmd *cmd)
{
	if (ft_middle_pipe_cmds(cmd) != SUCCESS)
		return (ERROR);
	if (cmd->id != 0 && !cmd->next)
	{
		if (dup2(cmd->pipe_in, STDIN_FILENO) < 0)
			return (ft_perror("dup2 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close syscall"), ERROR);
	}
	if (cmd->id == 0 && cmd->next)
	{
		if (dup2(cmd->pipe_out, STDOUT_FILENO) < 0)
			return (ft_perror("dup2 syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_out) < 0)
			return (ft_perror("close syscall"), ERROR);
		if (!ft_is_builtin(cmd) && close(cmd->pipe_in) < 0)
			return (ft_perror("close syscall"), ERROR);
	}
	return (SUCCESS);
}

int	ft_close_pipe_in_parent(t_cmd *cmd)
{
	if (cmd->id != 0 && cmd->next)
	{
		if (close(cmd->pipe_in) < 0)
			return (ft_perror("close syscall"), ERROR);
	}
	if (cmd->next)
	{
		if (close(cmd->pipe_out) < 0)
			return (ft_perror("close syscall"), ERROR);
	}
	if (!cmd->next && cmd->id != 0)
	{
		if (close(cmd->pipe_in) < 0)
			return (ft_perror("close syscall"), ERROR);
	}
	return (SUCCESS);
}
