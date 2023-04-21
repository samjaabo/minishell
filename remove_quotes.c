/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:40:58 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 14:15:18 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/*----------------------------------------------------------------*/

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

char	*rm_quote(char **str, int i, int j)
{
	char	*s;
	int		len;
	int		quote;

	s = NULL;
	if (!nb_quotes(*str))
		return (free(*str), ft_strdup(*str));
	len = ft_strlen(*str) - nb_quotes(*str) * 2;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (*(*str + i))
	{
		if (*(*str + i) == 34 || *(*str + i) == 39)
		{
			quote = *(*str + i++);
			while (*(*str + i) != quote)
				s[j++] = *(*str + i++);
			i++;
		}
		else
			s[j++] = *(*str + i++);
	}
	s[j] = '\0';
	return (free(*str), s);
}
