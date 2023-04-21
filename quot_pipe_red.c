/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_pipe_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:27:48 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 14:14:26 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_close_quote(char *str)
{
	int	i;
	int	check;
	int	character;

	i = -1;
	check = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			check = 1;
			character = str[i];
			while (check && str[++i])
			{
				if (str[i] == character)
					check = 0;
			}
		}
	}
	return (check);
}

/*----------------------------------------------------------------*/

static int	pipe_(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == 124)
		return (1);
	while (str[i])
	{
		if (str[i] == 124)
		{
			i++;
			while (str[i] && ft_space(str[i]))
				i++;
			if (!str[i] || str[i] == 124)
				return (1);
		}
		i++;
	}
	return (0);
}

/*----------------------------------------------------------------*/

static int	red_here_doc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str [i] == 60 || str[i] == 62)
		{
			if ((str[i] == 60 && str[i + 1] == 60)
				|| (str[i] == 62 && str[i + 1] == 62))
				i++;
			i++;
			while (str[i] && ft_space(str[i]))
				i++;
			if (!str[i] || str[i] == 124 || str[i] == 60 || str[i] == 62)
				return (1);
		}
			i++;
	}
	return (0);
}

/*----------------------------------------------------------------*/

static int	white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_space(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/*----------------------------------------------------------------*/

char	**syntax_and_split(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = NULL;
	if (!white_space(str))
	{
		if (open_close_quote(str) || pipe_(str) || red_here_doc(str))
		{
			ft_error("error", "invalid syntax");
			return (NULL);
		}
		split = split_cmd_line(str);
	}
	return (split);
}
