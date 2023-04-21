/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:52:22 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_single_quote(char **str, int hd, int j)
{
	int	qu;

	if (hd)
	{
		qu = *(*str + j++);
		while (*(*str + j) && *(*str + j) != qu)
		{
			if (*(*str + j) == '$')
			{
				expand_variable(str, &j);
				break ;
			}
			j++;
		}
	}
	else
	{
		j++;
		while (*(*str + j) != 39)
			j++;
		j++;
	}
	return (j);
}

/*----------------------------------------------------------------*/

static void	eliminate_dollar(char **str, int i)
{
	char	*expanded;
	int		j;

	expanded = malloc(ft_strlen(*str) * sizeof(char));
	if (!expanded)
		return ;
	j = 0;
	while (j < i)
	{
		expanded[j] = *(*str + j);
		j++;
	}
	while (*(*str + j + 1))
	{
		expanded[j] = *(*str + j + 1);
		j++;
	}
	expanded[j] = '\0';
	free(*str);
	*str = expanded;
}

/*----------------------------------------------------------------*/

void	var_special_case(char **str)
{
	int	i;

	i = 0;
	while (*(*str + i))
	{
		if (*(*str + i) == 34 || *(*str + i) == 39)
		{
			i++;
			while (*(*str + i) != 34 && *(*str + i) != 39)
				i++;
			i++;
		}
		else if (*(*str + i) == '$'
			&& (*(*str + i + 1) == 34 || *(*str + i + 1) == 39))
			eliminate_dollar(str, i);
		else
			i++;
	}
}

/*----------------------------------------------------------------*/

void	find_variable(char **str, int hd, int i)
{
	while (*(*str + i))
	{
		if (*(*str + i) == 39)
			i = skip_single_quote(str, hd, i);
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
		if (*(*str + i) == '$' && !hd
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
