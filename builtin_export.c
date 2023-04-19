/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:33:39 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/19 17:29:51 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_error_not_valid(char *str)
{
	write(2, "minishell: export: ", 19);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	g_data.exit_status = GENERAL_ERROR;
}

void	ft_empty_export(char **args)
{
	if (!args || !args[0] || args[1])
		return ;
	selection_sort_vars();
	g_data.exit_status = 0;
}

int	ft_isnot_valid_identifier(char *str, char stop)
{
	int	i;
	static int	status = 0;

	if (!str && !stop)
	{
		i = status;
		status = SUCCESS;
		return (i);
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
			status = GENERAL_ERROR;
			return (ft_error_not_valid(str), ERROR);
	}
	i = 0;
	while (str[i] && str[i] != stop)
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			status = GENERAL_ERROR;
			return (ft_error_not_valid(str), ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

int	ft_exp_append(char *str)
{
	char	*s;
	char	*join;
	char	c;

	if (!ft_strchr(str, '='))
		return (FALSE);
	if (*(ft_strchr(str, '=') - 1) != '+')
		return (FALSE);
	s = ft_strnstr(str, "+=", ft_strlen(str));
	if (!s)
		return (FALSE);
	join = NULL;
	c = *s;
	*s = 0;
	s += 2;
	if (ft_getenv(str) < 0)
		join = ft_strjoin3(str, "=", s);
	else
		join = ft_strjoin3(str, g_data.env[ft_getenv(str)] + ft_strlen(str), s);
	if (!join)
		return (*s = c, ERROR);
	ft_unset(((char *[3]){"unset", str, NULL}));
	ft_export(((char *[3]){"export", join, NULL}));
	free(join);
	*s = c;
	return (TRUE);
}

void	ft_export(char **args)//recall malloc on args
{
	int		i;
	char	c;
	char	**arr;
	char	*s;

	i = 0;
	arr = NULL;
	g_data.exit_status = 0;
	ft_empty_export(args);
	while (args[++i])
	{
		if (ft_isnot_valid_identifier(args[i], '='))
			continue ;
		if (!ft_strchr(args[i], '=') && ft_getenv(args[i]) >= 0)
			continue ;
		if (!ft_strncmp(args[i], "PATH=", 5))
			g_data.default_path = FALSE;
		if (ft_exp_append(args[i]))
			continue ;
		s = ft_strchr(args[i], '=');
		if (!s)
			s = ft_strchr(args[i], 0);
		c = *s;
		*s = '\0';
		ft_unset(((char *[3]){"unset", args[i], NULL}));
		*s = c;
		if (g_data.exit_status != SUCCESS)
			return ;
		arr = ft_realloc(g_data.env, ft_strdup(args[i]));
		if (!arr)
			return (ft_perror("malloc"));
		g_data.env = arr;
	}
	g_data.exit_status = ft_isnot_valid_identifier(NULL, 0);
}
