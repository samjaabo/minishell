/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_for_update(char **last, int n)
{
	char	*path;

	if (n == 1)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (1);
		free(*last);
		*last = path;
		return (1);
	}
	if (n == 2)
		return (free(*last), 1);
	return (0);
}

void	ft_pwd(int n)
{
	char		*path;
	static char	*last;

	if (ft_check_for_update(&last, n))
		return ;
	path = getcwd(NULL, 0);
	if (!path)
	{
		if (!last)
		{
			ft_perror("pwd: error retrieving current directory:"
				" getcwd: cannot access parent directories:");
			return ;
		}
		printf("%s\n", last);
		g_data.exit_status = 0;
		return ;
	}
	free(last);
	last = path;
	printf("%s\n", path);
	g_data.exit_status = 0;
}

void	ft_update_oldpwd(void)
{
	char	*var;
	char	*path;

	if (ft_getenv("OLDPWD") < 0)
		return ;
	path = getcwd(NULL, 0);
	var = ft_strjoin3("OLDPWD", "=", path);
	if (!var)
		return (free(path), ft_perror("malloc"));
	ft_export(((char *[3]){"export", var, NULL}));
	free(var);
	free(path);
}

void	ft_update_pwd(void)
{
	char	*var;
	char	*path;

	if (ft_getenv("PWD") < 0)
		return ;
	path = getcwd(NULL, 0);
	var = ft_strjoin3("PWD", "=", path);
	if (!var)
		return (free(path), ft_perror("malloc"));
	ft_export(((char *[3]){"export", var, NULL}));
	free(var);
	free(path);
}

void	ft_update_lastcmd(char **args)
{
	char	*var;
	int		i;

	if (!args)
		return ;
	i = 0;
	while (args[0] && args[i + 1])
		++i;
	var = ft_strjoin3("_", "=", args[i]);
	if (!var)
		return (ft_perror("malloc"));
	ft_export(((char *[3]){"export", var, NULL}));
	free(var);
}
