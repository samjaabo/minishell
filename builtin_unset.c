/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:39:20 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_getenv(char *var)
{
	int	i;
	int	len;
	int	lenvar;

	i = 0;
	len = ft_strlen(var);
	while (g_data.env && g_data.env[i])
	{
		lenvar = ft_strlen(g_data.env[i]);
		if (!ft_strncmp(g_data.env[i], var, len)
			&& (g_data.env[i][len] == '=' || g_data.env[i][len] == 0))
			return (i);
		++i;
	}
	return (-1);
}

char	**ft_realloc_env(int ignore)
{
	int		i;
	char	**arr;

	i = 0;
	arr = NULL;
	while (g_data.env[i])
	{
		if (i != ignore)
		{
			arr = ft_realloc(arr, g_data.env[i]);
			if (!arr)
			{
				ft_perror("malloc");
				g_data.exit_status = -1;
				ft_clear(arr);
				return (NULL);
			}
		}
		++i;
	}
	return (arr);
}

static void	ft_error_not_valid(char *str)
{
	write(2, "minishell: unset: ", 19);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	g_data.exit_status = GENERAL_ERROR;
}

int	ft_is_not_valid_identifier(char *str, char stop)
{
	int			i;
	static int	status = 0;

	if (!str && !stop)
		return (i = status, status = SUCCESS, i);
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		status = GENERAL_ERROR;
		return (ft_error_not_valid(str), ERROR);
	}
	i = 0;
	while (str[i] && str[i] != stop)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			status = GENERAL_ERROR;
			return (ft_error_not_valid(str), ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

void	ft_unset(char **args)
{
	int		i;
	int		var;
	char	**arr;

	i = 0;
	arr = NULL;
	g_data.exit_status = 0;
	errno = 0;
	while (args[++i])
	{
		if (ft_is_not_valid_identifier(args[i], 1))
			continue ;
		var = ft_getenv(args[i]);
		if (var < 0)
			continue ;
		arr = ft_realloc_env(var);
		if (errno)
			return ;
		free(g_data.env[var]);
		free(g_data.env);
		g_data.env = arr;
	}
	g_data.exit_status = ft_isnot_valid_identifier(NULL, 0);
}
