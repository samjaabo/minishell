/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:15:24 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/19 14:52:10 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	classing_files(t_cmd **ptr, char *str)
{
	if (str[0] == '<' && !str[1])
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("4"));
	else if (str[0] == '<' && str[0] == str[1] && !str[2])
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("2"));
	else if (str[0] == '>' && !str[1])
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("3"));
	else if (str[0] == '>' && str[0] == str[1] && !str[2])
		(*ptr)->types = ft_realloc((*ptr)->types, ft_strdup("1"));
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
