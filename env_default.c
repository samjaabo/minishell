/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:22:53 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iscwd_exists(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (FALSE);
	free(path);
	return (TRUE);
}

void	ft_init_env(void)
{
	char	*path;
	char	*join;
	char	*var;

	path = getcwd(NULL, 0);
	join = ft_strjoin3("PWD", "=", path);
	free(path);
	var = ft_strdup("OLDPWD");
	if (ft_getenv("OLDPWD") < 0)
		ft_export(((char *[3]){"export", var, NULL}));
	free(var);
	if (ft_getenv("PWD") < 0 && ft_iscwd_exists())
		ft_export(((char *[3]){"export", join, NULL}));
	free(join);
	var = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (ft_getenv("PATH") < 0)
	{
		ft_export(((char *[3]){"export", var, NULL}));
		g_data.default_path = TRUE;
	}
	free(var);
}

void	ft_shell_level(void)
{
	char	*s;
	char	*var;
	int		i;
	int		n;

	var = ft_strdup("SHLVL=1");
	if (ft_getenv("SHLVL") < 0)
		return (ft_export(((char *[3]){"export", var, NULL})), free(var));
	free(var);
	var = g_data.env[ft_getenv("SHLVL")];
	s = ft_strchr(var, '=');
	n = 1;
	if (s || s[1] != 0)
	{
		i = 0;
		while (ft_isdigit(s[++i]))
			;
		if (s[i] == 0)
			n = (int)ft_atoi(&s[1]) + 1;
	}
	s = ft_itoa(n);
	var = ft_strjoin3("SHLVL", "=", s);
	if (!var)
		return (free(s), ft_perror("malloc failed"));
	return (free(s), ft_export(((char *[3]){"export", var, NULL})), free(var));
}

char	*get_env(char *var)
{
	char	*all_var;
	int		i;

	all_var = ft_strjoin3(var, "=", NULL);
	i = -1;
	while (g_data.env && g_data.env[++i])
	{
		if (!ft_strncmp(all_var, g_data.env[i], ft_strlen(all_var)))
		{
			free(all_var);
			return (ft_strdup(&g_data.env[i][ft_strlen(var) + 1]));
		}
	}
	free(all_var);
	return (NULL);
}
