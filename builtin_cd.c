/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/16 22:02:34 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data	g_data;

void	ft_cd(char *s)
{
	int		var;
	char	*p;

	if (!s)
	{
		var = ft_getenv("HOME");
		if (var < 0)
			return (ft_error("cd", "HOME not set"));
		p = ft_strchr(g_data.env[var], '=');
		if (!p)
			return (ft_error("cd", "HOME not set"));
		s = ++p;
	}
	if (chdir(s) < 0)
	{
		ft_perror(s);
		return ;
	}
	// var = ft_getenv("PWD");
	// if (var >= 0 && ft_strchr(g_data.env[var], '='))
	// 	ft_update_var("OLDPWD", g_data.env[var]);
	// ft_update_var("PWD", s);
	g_data.exit_status = SUCCESS;
	ft_update_prompt_string();
}

int	ft_update_var_if_exists(char *var, char *value)
{
	char *s;

	s = ft_strjoin3(var, "=", value);
	if (!s)
		return (ft_perror("malloc"), ERROR);
	ft_export((char *[]){"export", s, NULL});
	free(s);
	return (SUCCESS);
}
