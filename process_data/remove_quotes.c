/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:40:58 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/17 18:12:28 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	nb_quotes(const char *str)
{
	int	i;
	int	check;
	int	quote;

	i = -1;
	check = 0;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			check++;
			quote = str[i++];
			while (str[i] != quote)
				i++;
		}
	}
	return (check);
}

/*----------------------------------------------------------------*/

char	*remove_quote(const char *str)
{
	char	*s;
	int		i;
	int		j;
	int		len;
	int		quote;

	s = NULL;
	if (!nb_quotes(str))
		return (ft_strdup(str));
	len = ft_strlen(str) - nb_quotes(str) * 2;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote = str[i++];
			while (str[i] != quote)
				s[j++] = str[i++];
			i++;
		}
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}
