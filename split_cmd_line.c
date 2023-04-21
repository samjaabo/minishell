/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:23:17 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 14:13:45 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*pass_the_quotes(char *str)
{
	char	check;

	check = *(str++);
	while (*str && *str != check)
		str++;
	str++;
	while (*str && !ft_space(*str) && *str != 34 && *str != 39
		&& *str != '|' && *str != '<' && *str != '>')
		str++;
	return (str);
}

/*----------------------------------------------------------------*/

static void	nb_of_strings(char const *str, int *count)
{
	*count = 0;
	while (*str)
	{
		if (!ft_space(*str))
		{
			(*count)++;
			if (*str == 124 || *str == 60 || *str == 62)
			{
				str++;
				if (*str == 60 || *str == 62)
					str++;
				if (*str && !ft_space(*str))
					(*count)++;
			}
		}
		while (*str && !ft_space(*str) && *str != 34 && *str != 39
			&& *str != '|' && *str != '<' && *str != '>')
			str++;
		while (*str == 34 || *str == 39)
			str = pass_the_quotes((char *)str);
		while (*str && ft_space(*str))
			str++;
	}
}

/*----------------------------------------------------------------*/

static int	word_len(char const *s)
{
	int	i;
	int	check;

	if (s[0] == 124)
		return (1);
	else if (s[0] == 60 || s[0] == 62)
	{
		if (s[1] == 60 || s[1] == 62)
			return (2);
		return (1);
	}
	i = 0;
	while (s[i] && !ft_space(s[i]))
	{
		if (s[i] == 34 || s[i] == 39)
		{
			check = s[i++];
			while (s[i] && s[i] != check)
				i++;
		}
		if (s[i] == 124 || s[i] == 60 || s[i] == 62)
			return (i);
		i++;
	}
	return (i);
}

/*----------------------------------------------------------------*/

static char	*ft_word(char const *s, int *j)
{
	char	*str;

	*j = word_len(s);
	str = malloc((*j + 1) * sizeof(char));
	if (!str)
		return (0);
	str[*j] = '\0';
	ft_memcpy(str, s, *j);
	return (str);
}

/*----------------------------------------------------------------*/

char	**split_cmd_line(char const *s)
{
	char	**sep;
	int		count;
	int		i;
	int		j;

	nb_of_strings(s, &count);
	sep = malloc((count + 1) * sizeof(char *));
	if (!sep)
		return (0);
	sep[count] = NULL;
	i = 0;
	j = 0;
	while (*s)
	{
		if (!ft_space(*s))
		{
			sep[i] = ft_word(s, &j);
			if (!sep[i++])
				return (ft_clear(sep), NULL);
		}
		s = s + j;
		while (*s && ft_space(*s))
			s++;
	}
	return (sep);
}
