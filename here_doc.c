/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:45:04 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/12 11:52:32 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*ft_read(void)
{
	char	*s;
	char	*tmp;
	char	*buf;
	int		d;

	errno = 0;
    s = ft_calloc(1, sizeof(char));
	buf = ft_calloc(2, sizeof(char));
	if (!buf || !s)
		return (free(s), ft_perror("malloc"), NULL);
	write(1, "\e[1;97mheredoc>\e[0m ", 21);
	while (buf[0] != '\n' && !g_data.here_doc_control_c)
	{
		d = read(STDIN_FILENO, buf, 1);
		if (d < 0)
			return (free(s), free(buf), NULL);
		if (d == 0 && s[0] == 0)
			return (free(s), free(buf), write(1, "\n", 1), NULL);
		tmp = ft_strjoin3(s, buf, NULL);
		free(s);
		s = tmp;
		if (!tmp)
			return (free(buf), ft_perror("malloc"), NULL);
	}
	return (free(buf), s);
}

static int	ft_here_doc(char *limiter)
{
	char	*buff;
	int		fds[2];

	if (pipe(fds) < 0)
		return (ERROR);
	while (!g_data.here_doc_control_c)
	{
		buff = ft_read();
		//printf("%s", buff);
		if (!buff && errno == 0)
			break ;
		if (!buff && errno != 0)
			return (close(fds[0]), close(fds[1]), ERROR);
		if (!ft_strncmp(buff, limiter, ft_strlen(limiter))
				&& buff[ft_strlen(limiter)] == '\n')
		{
			free(buff);
			break ;
		}
		write(fds[1], buff, ft_strlen(buff));
		//write(fds[1], "\n", 1);
		free(buff);
	}
	if (g_data.here_doc_control_c)
		return (close(fds[0]), close(fds[1]), -1);
	return (close(fds[1]), fds[0]);
}

static int	ft_here_doc_on_control_c(t_cmd *cmd)
{
	if (!g_data.here_doc_control_c)
		return (SUCCESS);
	while (cmd)
	{
		if (cmd->here_doc >= 0)
			close(cmd->here_doc);
		cmd = cmd->next;
	}
	g_data.status = STATUS_READIND;
	return (SUCCESS);
}

int	ft_do_here_doc(t_cmd *cmd)
{
	int	i;
	t_cmd	*tmp;

	g_data.status = STATUS_HERE_DOC;
	g_data.here_doc_control_c = FALSE;
	tmp = cmd;
	while (cmd && !g_data.here_doc_control_c)
	{
		i = 0;
		while (cmd->redirs && cmd->redirs[i] && !g_data.here_doc_control_c)
		{
			if (ft_atoi(cmd->types[i]) == HERE_DOCUMENT)
			{
				close(cmd->here_doc);
				cmd->here_doc = ft_here_doc(cmd->redirs[i]);
			}
			++i;
		}
		cmd = cmd->next;
	}
	g_data.status = STATUS_EXECUTING;
	return (ft_here_doc_on_control_c(tmp));
}

