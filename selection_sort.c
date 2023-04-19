/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:56:19 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/19 14:52:20 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	valid_var(char *str)
{
	int	i;

	if (ft_isalpha(str[0]) || str[0] == 95)
	{
		i = 0;
		while (ft_isalnum(str[i]))
			i++;
		if (str[i] == '=' || !str[i])
			return (1);
	}
	return (0);
}

void	selection_sort(char **env, int len)
{
	char	*swp;
	int		i;
	int		j;
	int		min;

	i = -1;
	while (++i < len - 1)
	{
		min = i;
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[min], env[j]) > 0)
				min = j;
			j++;
		}
		swp = env[i];
		env[i] = env[min];
		env[min] = swp;
	}
}
