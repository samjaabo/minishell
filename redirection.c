/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:47:50 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0)
		return (ft_perror(file), ERROR);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_perror("dup2"), ERROR);
	if (close(fd) < 0)
		return (ft_perror("close"), ERROR);
	return (SUCCESS);
}

int	ft_write_truncate(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (ft_perror(file), ERROR);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_perror("dup2"), ERROR);
	if (close(fd) < 0)
		return (ft_perror("close"), ERROR);
	return (SUCCESS);
}

int	ft_file_to_stdin(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_perror(file), ERROR);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ft_perror("dup2"), ERROR);
	if (close(fd) < 0)
		return (ft_perror("close"), ERROR);
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
