/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:21 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/31 17:25:13 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rmdup(char *s, char c, int *n)
{
	char	*a;
	char	*b;

	a = s;
	b = s;
	while (*a == c)
		a++;
	while (*a)
	{
		if (*a == c)
			*b++ = c;
		while (*a == c)
			a++;
		if (*a != '\0')
			*b++ = *a++;
	}
	*b = '\0';
	a = ft_strchr(s, '\0');
	if (a > s && *--a == c)
		*a = '\0';
	while (*s)
		if (*s++ == c && ++(*n))
			*(s - 1) = '\0';
}

static char	**ft_clear(char *a, char **ar)
{
	char	**cp;

	free(a);
	cp = ar;
	while (*ar)
		free(*ar++);
	free(cp);
	return (NULL);
}

static char	**splitit(char *c, char *a, char **ar, int n)
{
	char	**cp;
	char	*start;

	start = a;
	cp = ar;
	while (n--)
	{
		*cp = ft_strdup(start);
		if (!*cp)
			return (ft_clear(a, ar));
		if (*cp++ == '\0' || (c[0] == '\0' && c[1] == '\0'))
		{
			free(a);
			free(*--cp);
			*ar = NULL;
			return (ar);
		}
		start = ft_strchr(start, '\0') + 1;
	}
	*cp = NULL;
	free(a);
	return (ar);
}

char	**ft_split(char const *s, char c)
{
	char	**ar;
	char	cc[2];
	char	*a;
	int		n;

	if (!s)
		return (NULL);
	n = 1;
	cc[0] = *s;
	cc[1] = c;
	a = ft_strdup(s);
	if (!a)
		return (NULL);
	ft_rmdup(a, c, &n);
	if (*a == '\0')
		n = 0;
	ar = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!ar)
	{
		free(a);
		return (NULL);
	}
	return (splitit(cc, a, ar, n));
}
