/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:02:21 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_home(void)
{
	char	*str;

	str = get_env("HOME");
	if (!str)
	{
		ft_error("cd", "Home not set");
		return ;
	}
	if (chdir(str) == -1)
	{
		ft_perror(str);
		free(str);
		return ;
	}
	free(str);
}

/*----------------------------------------------------------------*/

static void	go_dir_in_home(char *args)
{
	char	*str;
	char	*home;

	home = get_env("HOME");
	str = ft_strjoin3(home, &args[1], NULL);
	if (!str)
	{
		ft_error("cd", "HOME not set");
		return ;
	}
	if (chdir(str) == -1)
	{
		ft_perror(str);
		return ;
	}
	free(str);
	free(home);
}

/*----------------------------------------------------------------*/

void	ft_cd(char **args)
{
	char	*str;

	ft_update_oldpwd();
	g_data.exit_status = 0;
	if (!args[1] || (args[1][0] == 126 && !args[1][1]))
		go_home();
	else if (args[1][0] == 126 && args[1][1] == '/')
		go_dir_in_home(args[1]);
	else
	{
		str = getcwd(NULL, 0);
		if (!str && args[1][0] == '.' && !args[1][1])
		{
			write(2, "cd: error retrieving current directory: getcwd: cannot "
				"access parent directories: No such file or directory\n", 109);
			return (free(str));
		}
		if (chdir(args[1]) == -1)
			return (free(str), ft_perror(args[1]));
		free(str);
	}
	ft_pwd(1);
	ft_update_pwd();
	ft_update_prompt_string();
}
