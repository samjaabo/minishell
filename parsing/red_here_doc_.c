/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_here_doc_.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:43:18 by araqioui          #+#    #+#             */
/*   Updated: 2023/03/19 12:14:53 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	red_here_doc(char *str)
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
			while (str[i] && str[i] == 32)
				i++;
			if (!str[i] || str[i] == 124 || str[i] == 60 || str[i] == 62)
				return (1);
		}
			i++;
	}
	return (0);
}
