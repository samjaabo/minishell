/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:25:09 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/16 22:16:05 by samjaabo         ###   ########.fr       */
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

int	ft_redirection(t_cmd *cmd)
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

static int	ft_child(t_cmd *cmd, char *path)
{
	char	*s;

	if (signal(SIGQUIT, ft_control_slash) == SIG_ERR)
		return (ft_perror("siganl to set handler fail"), g_data.exit_status);
	if (ft_pipe_in_child(cmd) == ERROR)
		return (g_data.exit_status);
	if (ft_redirection(cmd) == ERROR)
		return (g_data.exit_status);
	ft_child_close_fds_copy();
	if (cmd->args)
	{
		s = ft_get_cmd_path(path, cmd->args[0]);
		free(cmd->args[0]);
		cmd->args[0] = s;
		if (!s)
			return (g_data.exit_status);
		//ft_export((cha **)((char [][4]){"export", "_", s, NULL})); if (!error) export "_=./command"
		//printf("%s\n", cmd->args[0]);
		execve(cmd->args[0], cmd->args, g_data.env);
		ft_perror(cmd->args[0]);
		g_data.exit_status=PERMISSION;
		return (g_data.exit_status);
	}
	return (g_data.exit_status);
}

int	ft_parent(t_cmd *cmd)
{
	if (!ft_is_builtin(cmd))
		ft_close_pipe_in_parent(cmd);
	ft_return_default_stdio();
	if (cmd->here_doc >= 0)
		close(cmd->here_doc);
	return (SUCCESS);
}

int	ft_exec(t_cmd *cmd, char *path)
{
	pid_t		pid;

	errno = 0;
	if (ft_do_here_doc(cmd) == ERROR || g_data.here_doc_control_c)//check for intrrupt Control-c
	{
		dup2(g_data.new_stdin, STDIN_FILENO);
		g_data.here_doc_control_c = FALSE;
		return (SUCCESS);
	}
	pid = -1337;
	while (cmd)
	{
		if (ft_pipe_in_parent(cmd) == ERROR)
			return(ERROR);
		if (ft_builtins(cmd) != SUCCESS)
			return (ERROR);
		if (!ft_is_builtin(cmd))
			pid = fork();
		if (pid == -1)
		{
			ft_perror("fork failed");
			break ;
		}
		if (pid == 0)
			return (exit(ft_child(cmd, path)), 0);
		ft_parent(cmd);
		if (!cmd->next)//id builtin is last dont wait exit_status
			pid = -1337;
		cmd = cmd->next;
	}
	//g_data.newline = FALSE;
	if (pid != -1337)
		waitpid(pid, &g_data.exit_status, 0);
	errno = 0;
	while (errno == 0)
		wait(NULL);
	//if (g_data.newline)
	//	write(1, "\n", 1);
	if (errno != ECHILD && errno != EINTR)
		return (ft_perror("wait syscall") ,ERROR);
	return (g_data.exit_status);
}
