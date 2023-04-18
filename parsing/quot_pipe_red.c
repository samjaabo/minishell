/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_pipe_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:27:48 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/18 11:53:58 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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
	while (str[i] && str[i] == 32)
		i++;
	if (str[i] == 124)
		return (1);
	while (str[i])
	{
		if (str[i] == 124)
		{
			i++;
			while (str[i] && str[i] == 32)
				i++;
			if (!str[i] || str[i] == 124)
				return (1);
		}
		i++;
	}
	return (0);
}

/*----------------------------------------------------------------*/

static int	skip_single_quote(char *str, int j)
{
	j++;
	while (str[j] != 39)
		j++;
	j++;
	return (j);
}

/*----------------------------------------------------------------*/

static void	find_variable(char **str, int i)
{
	while (*(*str + i))
	{
		if (*(*str + i) == 39)
			i = skip_single_quote(*str, i);
		if (*(*str + i) == 34)
		{
			i++;
			while (*(*str + i) && *(*str + i) != 34)
			{
				if (*(*str + i) == '$')
					expand_variable(str, &i);
				i++;
			}
			i++;
		}
		if (*(*str + i) == '$'
			&& (*(*str + i + 1) == 34 || *(*str + i + 1) == 39))
			eliminate_dollar(str, i);
		else if (*(*str + i) == '$'
			&& (*(*str + i + 1) != 34 || *(*str + i + 1) != 39))
			expand_variable(str, &i);
		if (*(*str + i) && *(*str + i) != 34
			&& *(*str + i) != 39 && *(*str + i) != '$')
			i++;
	}
}

/*----------------------------------------------------------------*/

char	**split_and_expand(char *str)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	if (!white_space(str))
	{
		if (open_close_quote(str) || pipe_(str) || red_here_doc(str))
		{
			printf("error: invalid syntax\n");
			return (NULL);
		}
		find_variable(&str, i);
		if (str[0])
			split = split_cmd_line(str);
		free(str);
	}
	return (split);
}

