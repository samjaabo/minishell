/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:56:45 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/09 17:04:58 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_fd_to_fd(int fd1, int fd2)
{
	int	fd[2];

	if (fd1 < 0 || fd2 < 0)
		return (ERROR);
	if (dup2(fd1, fd2) < 0)
		return (ft_perror("dup2 syscall"), ERROR);
	return (SUCCESS);
}

static int	ft_open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0666);
	if (fd < 0)
		return (ft_perror(file), ERROR);
	return (fd);
}

int ft_file_to_fd(char *file, int flags, int tofd)
{
	int fd;

	fd = ft_open_file(file, flags);
	return (ft_fd_to_fd(fd, tofd));
}