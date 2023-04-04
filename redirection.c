/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:47:50 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/02 16:08:56 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_here_doc(char *limiter)
{
	char	*buff;
	int		fds[2];

	if (pipe(fds) < 0)
		return (ERROR);
	while (1337)
	{
		write(1, "heredoc> ", 10);
		buff = get_next_line(0);
		if (!buff)
			break ;
		if (ft_strlen(buff) - 1 == ft_strlen(limiter)
			&& !ft_strncmp(buff, limiter, ft_strlen(limiter))
			&& buff[ft_strlen(limiter)] == '\n')
		{
			get_next_line(-100);
			free(buff);
			break ;
		}
		write(fds[1], buff, ft_strlen(buff));
		free(buff);
	}
	if (close(fds[1]) < 0)
		return (ERROR);
	if (dup2(fds[0], 0) < 0)
		return (ERROR);
	if (close(fds[0]) < 0)
		return (ERROR);
	return (SUCCESS);
}

int	ft_write_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ERROR);
	if (close(fd) < 0)
		return (ERROR);
	return (SUCCESS);
}

int	ft_write_truncate(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ERROR);
	if (close(fd) < 0)
		return (ERROR);
	return (SUCCESS);
}

int	ft_file_to_stdin(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ERROR);
	if (close(fd) < 0)
		return (ERROR);
	return (SUCCESS);
}
