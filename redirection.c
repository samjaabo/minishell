/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:47:50 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/10 19:45:34 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
