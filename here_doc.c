/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:45:04 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/10 22:10:17 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_here_doc(char *limiter)
{
	char	*buff;
	int		fds[2];

	if (read(0, 0, 0) < 0)
		return (ERROR);//control-c interrupt
	if (pipe(fds) < 0)
		return (ERROR);
	while (TRUE)
	{
		buff = readline("\e[1;97mheredoc>\e[0m ");
		if (!buff)
			break ;
		// printf("-->%s\n" , buff);
		if (!ft_strncmp(buff, limiter, ft_strlen(limiter) + 1))
		{
			free(buff);
			break ;
		}
		write(fds[1], buff, ft_strlen(buff));
		write(fds[1], "\n", 1);
		free(buff);
	}
	if (close(fds[1]) < 0)
		return (ERROR);
	if (read(0, 0, 0) < 0)
		return (close(fds[0]), -1);
	return (fds[0]);
}

static int	ft_here_doc_on_control_c(t_cmd *cmd)
{
	if (read(0, 0, 0) == 0)
		return (SUCCESS);
	while (cmd)
	{
		if (cmd->here_doc >= 0)
			close(cmd->here_doc);
		cmd = cmd->next;
	}
	if (dup2(g_data.new_stdin, STDIN_FILENO) < 0)
		return (ft_perror("dup2 hel1223o syscall") ,ERROR);
	g_data.status = STATUS_READIND;
	return (ERROR);
}

int	ft_do_here_doc(t_cmd *cmd)
{
	int	fd;
	int	i;
	t_cmd	*tmp;

	g_data.status = STATUS_HERE_DOC;
	tmp = cmd;
	while (cmd)
	{
		i = 0;
		fd = -1;
		while (cmd->redirs && cmd->redirs[i])
		{
			if (ft_atoi(cmd->types[i]) == HERE_DOCUMENT)
				fd = ft_here_doc(cmd->redirs[i]);
			++i;
		}
		cmd->here_doc = fd;
		cmd = cmd->next;
	}
	g_data.status = STATUS_EXECUTING;
	return (ft_here_doc_on_control_c(tmp));
}

