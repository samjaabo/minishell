/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:48:26 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/07 17:50:27 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_free(char **str)
{
	int	i;

	if (str)
	{
		if (str[0])
			free(str[0]);
		i = 1;
		while (str[i])
			free(str[i++]);
		free(str);
	}
	return (NULL);
}
