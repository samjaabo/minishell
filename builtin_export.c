/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:33:39 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_empty_export(char **args)
{
	g_data.exit_status = 0;
	if (!args || !args[0] || args[1])
		return ;
	selection_sort_vars();
}

int	ft_exp_append(char *str)
{
	char	*s;
	char	*join;
	char	c;

	if (!ft_strchr(str, '=') || *(ft_strchr(str, '=') - 1) != '+')
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
	else if (!ft_strchr(g_data.env[ft_getenv(str)], '='))
		join = ft_strjoin3(g_data.env[ft_getenv(str)], "=", s);
	else
		join = ft_strjoin3(g_data.env[ft_getenv(str)], s, NULL);
	if (!join)
		return (*(s - 2) = c, ERROR);
	ft_unset(((char *[3]){"unset", str, NULL}));
	ft_export(((char *[3]){"export", join, NULL}));
	return (free(join), *(s - 2) = c, TRUE);
}

static int	ft_check_for_continue(char **args, int i)
{
	if (ft_isnot_valid_identifier(args[i], '='))
		return (1);
	if (!ft_strchr(args[i], '=') && ft_getenv(args[i]) >= 0)
		return (1);
	if (!ft_strncmp(args[i], "PATH=", 5))
		g_data.default_path = FALSE;
	if (ft_exp_append(args[i]))
		return (1);
	return (0);
}

void	ft_export(char **args)
{
	int		i;
	char	c;
	char	**arr;
	char	*s;

	i = 0;
	arr = NULL;
	ft_empty_export(args);
	while (args[++i])
	{
		if (ft_check_for_continue(args, i))
			continue ;
		s = ft_strchr(args[i], '=');
		if (!s)
			s = ft_strchr(args[i], 0);
		c = *s;
		*s = 0;
		ft_unset(((char *[3]){"unset", args[i], NULL}));
		*s = c;
		arr = ft_realloc(g_data.env, ft_strdup(args[i]));
		if (!arr)
			return (ft_perror("malloc"));
		g_data.env = arr;
	}
	g_data.exit_status = ft_isnot_valid_identifier(NULL, 0);
}
