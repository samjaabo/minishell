/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:25:09 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_close_fds_copy(void)
{
	close(g_data.new_stdin);
	close(g_data.new_stdout);
}

static int	ft_child(t_cmd *cmd, char *path)
{
	char	*s;

	s = 0;
	if (signal(SIGQUIT, ft_control_slash) == SIG_ERR)
		return (ft_perror("siganl to set handler fail"), g_data.exit_status);
	if (ft_pipe_in_child(cmd) == ERROR)
		return (g_data.exit_status);
	if (ft_redirection(cmd) == ERROR)
		return (g_data.exit_status);
	ft_child_close_fds_copy();
	if (cmd->args && !ft_exec_builtins(cmd))
	{
		s = ft_get_cmd_path(path, cmd->args[0]);
		free(cmd->args[0]);
		cmd->args[0] = s;
		if (!s)
			return (g_data.exit_status);
		execve(cmd->args[0], cmd->args, g_data.env);
		ft_perror(cmd->args[0]);
		g_data.exit_status = PERMISSION;
		return (g_data.exit_status);
	}
	return (g_data.exit_status);
}

static int	ft_exec_cmds(t_cmd *cmd, char *path, pid_t *pid)
{
	while (cmd)
	{
		if (ft_pipe_in_parent(cmd) == ERROR)
			return (ERROR);
		if (ft_builtins(cmd) != SUCCESS)
			return (ERROR);
		if (!ft_is_builtin(cmd))
			*pid = fork();
		if (*pid == -1)
		{
			*pid = -2;
			ft_perror("fork failed");
			return (SUCCESS);
		}
		if (*pid == 0)
			return (exit(ft_child(cmd, path)), 0);
		if (!ft_is_builtin(cmd))
			ft_close_pipe_in_parent(cmd);
		ft_return_default_stdio();
		if (cmd->here_doc >= 0)
			close(cmd->here_doc);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

static int	ft_wait(pid_t pid)
{
	errno = 0;
	if (pid >= 0)
		waitpid(pid, &g_data.exit_status, 0);
	if (pid >= 0 && WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	else if (pid >= 0 && WIFSIGNALED(g_data.exit_status))
	{
		g_data.exit_status = WTERMSIG(g_data.exit_status) + 128;
		ft_print_signal();
	}
	errno = 0;
	while (errno == 0)
		wait(NULL);
	if (errno != ECHILD && errno != EINTR)
		return (ft_perror("wait syscall"), ERROR);
	return (0);
}

int	ft_exec(t_cmd *cmd, char *path)
{
	pid_t	pid;

	errno = 0;
	if (ft_do_here_doc(cmd) == ERROR || g_data.here_doc_control_c)
	{
		dup2(g_data.new_stdin, STDIN_FILENO);
		g_data.here_doc_control_c = FALSE;
		return (ERROR);
	}
	pid = -2;
	if (ft_exec_cmds(cmd, path, &pid) != SUCCESS)
		return (ERROR);
	return (ft_wait(pid));
}
