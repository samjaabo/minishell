/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:07:06 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/15 14:39:38 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data	g_data;

static int	ft_check_args(const char *path, const char *cmd)
{
	struct stat info;
	
	if (!path || !cmd)
		return (ERROR);
	if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
		return (ft_error(cmd, "is a directory"), g_data.exit_status=126, ERROR);
	if (!cmd[0] || (!path[0] && !ft_strrchr(cmd, '/')))
		return (ft_error(cmd, "command not found"), g_data.exit_status=127, ERROR);
	return (SUCCESS);
}

char	*ft_get_cmd_path(const char *path, const char *cmd)
{
	char	**paths;
	char	*file;
	int		i;

	if (ft_check_args(path, cmd) == ERROR)
		return (NULL);
	if (ft_strrchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_mysplit(path, ':');
	if (!paths)
		return (ft_perror("malloc"), NULL);
	i = 0;
	while (paths[i])
	{
		file = ft_strjoin3(paths[i++], "/", cmd);
		if (!file)
			return (ft_clear(paths), ft_perror("malloc"), file);
		if (access(file, F_OK) == 0)
			return (ft_clear(paths), file);
		free(file);
	}
	g_data.exit_status=CMD_NOT_FOUND;
	return (ft_clear(paths), ft_error(cmd, "command not found"), NULL);
}