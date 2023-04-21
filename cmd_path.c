/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:07:06 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_args(const char *path, const char *cmd)
{
	struct stat	info;

	if (!path && !ft_strchr(cmd, '/'))
	{
		ft_error(cmd, "command not found");
		return (g_data.exit_status = 127, ERROR);
	}
	if (stat(cmd, &info) == 0 && S_ISDIR(info.st_mode))
	{
		ft_error(cmd, "is a directory");
		return (g_data.exit_status = 126, ERROR);
	}
	if (!cmd[0] || (path && !path[0] && !ft_strrchr(cmd, '/')))
	{
		ft_error(cmd, "command not found");
		return (g_data.exit_status = 127, ERROR);
	}
	return (SUCCESS);
}

char	*ft_get_cmd_path(const char *path, const char *cmd)
{
	char	**paths;
	char	*file;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_check_args(path, cmd) == ERROR)
		return (NULL);
	if (ft_strrchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(path, ':');
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
	ft_error(cmd, "command not found");
	return (g_data.exit_status = 127, ft_clear(paths), NULL);
}
