/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:15:24 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 14:02:23 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_len(char **splited)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (splited[++i])
		if (splited[i][0] == 124)
			count++;
	return (count);
}

/*----------------------------------------------------------------*/

void	fill_args(t_cmd **ptr, char **str)
{
	int	j;

	j = check_var_quotes(*str, 0);
	if (j)
		put_quotes(str, j);
	find_variable(str, 0, 0);
	*str = rm_quote(str, 0, 0);
	if (!(*ptr)->args)
	{
		if (!(**str))
			(*ptr)->args = ft_realloc(NULL, ft_strdup(""));
		else if (j)
			(*ptr)->args = ft_split(*str, ' ');
		else
			(*ptr)->args = ft_realloc((*ptr)->args, ft_strdup(*str));
	}
	else
		(*ptr)->args = ft_realloc((*ptr)->args, ft_strdup(*str));
}

/*----------------------------------------------------------------*/

int	check_var_quotes(char *str, int *qu)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (qu)
		*qu = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (qu)
				*qu = 1;
			i++;
			while (str[i] && str[i] != 39 && str[i] != 34)
					i++;
			i++;
		}
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			j++;
	}
	return (j);
}

/*----------------------------------------------------------------*/

void	classing_files(t_cmd **ptr, char *str, int qu)
{
	if (str[0] == '<' && !str[1])
	{
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("4"));
		(*ptr)->quote = ft_realloc((*ptr)->quote, ft_strdup("0"));
	}
	else if (str[0] == '<' && str[0] == str[1] && !str[2])
	{
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("2"));
		if (qu)
			(*ptr)->quote = ft_realloc((*ptr)->quote, ft_strdup("0"));
		else
			(*ptr)->quote = ft_realloc((*ptr)->quote, ft_strdup("1"));
	}
	else if (str[0] == '>' && !str[1])
	{
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("3"));
		(*ptr)->quote = ft_realloc((*ptr)->quote, ft_strdup("0"));
	}
	else if (str[0] == '>' && str[0] == str[1] && !str[2])
	{
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("1"));
		(*ptr)->quote = ft_realloc((*ptr)->quote, ft_strdup("0"));
	}
}

/*----------------------------------------------------------------*/

t_cmd	*process_data(char **splited)
{
	t_cmd	*lst;
	int		size;
	int		i;

	lst = NULL;
	size = list_len(splited) + 1;
	i = -1;
	while (++i < size)
		ft_lstadd_back(&lst, ft_lstnew(i));
	fill_the_list(&lst, splited, 0, 0);
	ft_clear(splited);
	return (lst);
}
