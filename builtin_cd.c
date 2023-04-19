/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:02:21 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/19 16:42:20 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	go_home(void)
{
	char	*str;

	str = get_env("HOME");
	if (!str)
	{
		printf("error: cd: HOME not set\n");
		return ;
	}
	if (chdir(str) == -1)
	{
		perror("chdir ");
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
	{
		go_home();
	}
	else if (args[1][0] == 126 && args[1][1] == '/')
	{
		go_dir_in_home(args[1]);
	}
	else
	{
		str = getcwd(NULL, 0);
		if (!str && args[1][0] == '.' && !args[1][1])
		{
			write(2, "cd: error retrieving current directory: getcwd: cannot ", 56);
			write(2, "access parent directories: No such file or directory\n", 54);
		}
		if (chdir(args[1]) == -1)
			ft_perror(args[1]);
		if (str)
			free(str);
	}
	ft_pwd(1);
	ft_update_pwd();
	ft_update_prompt_string();
}

// void	ft_cd(char *s)
// {
// 	int		var;
// 	char	*p;

// 	if (!s)
// 	{
// 		var = ft_getenv("HOME");
// 		if (var < 0)
// 			return (ft_error("cd", "HOME not set"));
// 		p = ft_strchr(g_data.env[var], '=');
// 		if (!p)
// 			return (ft_error("cd", "HOME not set"));
// 		s = ++p;
// 	}
// 	if (chdir(s) < 0)
// 	{
// 		ft_perror(s);
// 		return ;
// 	}
// 	// var = ft_getenv("PWD");
// 	// if (var >= 0 && ft_strchr(g_data.env[var], '='))
// 	// 	ft_update_var("OLDPWD", g_data.env[var]);
// 	// ft_update_var("PWD", s);
// 	g_data.exit_status = SUCCESS;
// 	ft_update_prompt_string();
// }

// int	ft_update_var_if_exists(char *var, char *value)
// {
// 	char *s;

// 	s = ft_strjoin3(var, "=", value);
// 	if (!s)
// 		return (ft_perror("malloc"), ERROR);
// 	ft_export((char *[]){"export", s, NULL});
// 	free(s);
// 	return (SUCCESS);
// }
