/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:07:06 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 22:47:04 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_check_args(const char *path, const char *cmd)
{
	if (!path || !cmd)
		return (ERROR);
	if (!cmd[0])
		return (ft_error(cmd, "command not found"), ERROR);
	if (ft_strrchr(cmd, '/') && !ft_strrchr(cmd, '/')[1])
	{
		if (access(cmd, F_OK) == 0)
			ft_error(cmd, "is a directory");
		else
			ft_error(cmd, "No such file or directory");
		return (ERROR);
	}
	if (ft_strrchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (ft_error(cmd, "No such file or directory"), ERROR);
	}
	return (SUCCESS);
}

t_mallochar	*ft_get_cmd_path(const char *path, const char *cmd)
{
	char	**paths;
	char	*s;
	int		i;

	if (ft_check_args(path, cmd) == ERROR)
		return (NULL);
	paths = ft_mysplit(path, ':');
	if (!paths)
		return (ft_perror("malloc"), NULL);
	if (ft_strrchr(cmd, '/'))
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		s = ft_strjoin3(paths[i++], "/", cmd);
		if (!s)
			return (ft_clear(paths), ft_perror("malloc"), s);
		if (access(s, F_OK) == 0)
			return (ft_clear(paths), s);
		free(s);
	}
	return (ft_clear(paths), ft_error(cmd, "command not found"), NULL);
}