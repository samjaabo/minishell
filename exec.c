/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:25:09 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/13 22:52:12 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data g_data;

void	ft_child_close_fds_copy(void)
{
	close(g_data.new_stdin);
	close(g_data.new_stdout);
	close(g_data.new_stderr);
}

int	ft_return_default_stdio(void)
{
	if (dup2(g_data.new_stdin, STDIN_FILENO) < 0)
		return (ERROR);
	if (dup2(g_data.new_stdout, STDOUT_FILENO) < 0)
		return (ERROR);
	if (dup2(g_data.new_stderr, STDERR_FILENO) < 0)
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
		if (ft_atoi(cmd->types[i]) == HERE_DOCUMENT && cmd->here_doc != -1)
		{
			ret = dup2(cmd->here_doc, STDIN_FILENO);
			ret = close(cmd->here_doc);
			cmd->here_doc = -1;
		}
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

void ft_lsof(void)
{
	char id[55]="lsof -p ";

	sprintf(id+8, "%d",getpid());
	printf("%s\n", id);
	system(id);
}

static int	ft_child(t_cmd *cmd, char *path, char **env)
{
	char	*s;

	signal(SIGQUIT, ft_control_slash);
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
	//ft_lsof();
	if (cmd->args)
	{
		execve(cmd->args[0], cmd->args, g_data.env);
		return (ft_perror(cmd->args[0]), ERROR);
	}
	return (SUCCESS);
}

int	ft_parent(t_cmd *cmd)
{
	ft_close_pipe_in_parent(cmd);
	ft_return_default_stdio();
	if (cmd->here_doc >= 0)
		close(cmd->here_doc);
	return (SUCCESS);
}

int	ft_exec(t_cmd *cmd, char *path, char **env)
{
	pid_t		pid;

	errno = 0;
	g_data.control = 0;
	if (ft_do_here_doc(cmd) == ERROR || g_data.here_doc_control_c)//check for intrrupt Control-c
	{
		dup2(g_data.new_stdin, STDIN_FILENO);
		g_data.here_doc_control_c = FALSE;
		return (SUCCESS);
	}
	pid = 1;
	while (cmd)
	{
		if (ft_pipe_in_parent(cmd) == ERROR)
			return(ERROR);
		if (ft_builtins(cmd) != IS_BUILTIN)
			pid = fork();
		if (pid < 0)
			return (ft_perror("fork syscall"), ERROR);
		if (pid == 0)
			return (ft_child(cmd, path, env), exit(0), 0);
		ft_parent(cmd);
		cmd = cmd->next;
	}
	while (wait(&g_data.exit_status) != -1)
		;
	if (errno != ECHILD && errno != EINTR)
		return (ft_perror("wait syscall") ,ERROR);
	return (g_data.exit_status);
}
