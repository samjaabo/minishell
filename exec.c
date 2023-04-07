/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:25:09 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/07 16:28:20 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_child_close_fds_copy(void)
{
	close(NEW_STDIN);
	close(NEW_STDOU);
	close(NEW_STDER);
}

void	ft_child_close_uneeded_fds(void)
{
	close(0);
	close(1);
	close(2);
}

int	ft_return_default_stdio(void)
{
	if (dup2(NEW_STDIN, STDIN_FILENO) < 0)
		return (ERROR);
	if (dup2(NEW_STDOU, STDOUT_FILENO) < 0)
		return (ERROR);
	if (dup2(NEW_STDER, STDERR_FILENO) < 0)
		return (ERROR);
	return (SUCCESS);
}

int	ft_dup_default_stdio(void)
{
	if (dup2(STDIN_FILENO, NEW_STDIN) < 0)
		return (ERROR);
	if (dup2(STDOUT_FILENO, NEW_STDOU) < 0)
		return (ERROR);
	if (dup2(STDERR_FILENO, NEW_STDER) < 0)
		return (ERROR);
	return (SUCCESS);
}

static int	ft_redirection(t_cmd *cmd)
{
	int	ret;
	int	i;

	ret = SUCCESS;
	i = 0;
	while (cmd && cmd->redirs && cmd->redirs[i] && ret != ERROR)
	{
		if (ft_atoi(cmd->types[i]) == HERE_DOCUMENT)
			ret = ft_here_doc(cmd->redirs[i]);
		else if (ft_atoi(cmd->types[i]) == FILE_TO_STDIN)
			ret = ft_file_to_stdin(cmd->redirs[i]);
		else if (ft_atoi(cmd->types[i]) == WRITE_TO_FILE)
			ret = ft_write_truncate(cmd->redirs[i]);
		else if (ft_atoi(cmd->types[i]) == APPEND_TO_FILE)
			ret = ft_write_append(cmd->redirs[i]);
		++i;
	}
	return (ret);
}

static int	ft_child(t_cmd *cmd, char *path, char **env)
{
	char	*s;

	if (cmd->args)
	{
		s = ft_get_cmd_path(path, cmd->args[0]);
		free(cmd->args[0]);
		cmd->args[0] = s;
		if (!s)
			return (ERROR);
	}
	if (ft_pipe_in_child(cmd) == ERROR)
		return (ERROR);
	if (ft_redirection(cmd) == ERROR)
		return (ERROR);
	ft_child_close_fds_copy();
	if (cmd->args)
	{
		execve(cmd->args[0], cmd->args, env);
		return (ft_perror(cmd->args[0]), ERROR);
	}
	ft_child_close_uneeded_fds();
	return (SUCCESS);
}

int	ft_parent(t_cmd *cmd)
{
	if (cmd->std_in > 5 && close(cmd->std_in) < 0)
		return (ft_perror("close syscall"), ERROR);
	if (cmd->std_out > 5 && close(cmd->std_out) < 0)
		return (ft_perror("close syscall"), ERROR);
	ft_return_default_stdio();
	return (SUCCESS);
}

int	ft_exec(t_cmd *cmd, char *path, char **env)
{
	pid_t		pid;
	int			status;

	status = SUCCESS;
	while (cmd)
	{
		if (ft_pipe_in_parent(cmd) == ERROR)
				return(ERROR);
		pid = fork();
		if (pid < 0)
			return (ft_perror("fork syscall"), ERROR);
		if (pid == 0)
			return (exit(ft_child(cmd, path, env)), 0);
		ft_parent(cmd);
		cmd = cmd->next;
	}
	while (wait(&status) != -1)//be aware of intrrupt
		;
	if (errno != ECHILD && errno != EINTR)
		return (ft_perror("wait syscall") ,ERROR);
	return (status);
}
