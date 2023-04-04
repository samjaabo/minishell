/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:25:26 by samjaabo          #+#    #+#             */
/*   Updated: 2023/03/27 23:16:44 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s && *s++)
		++n;
	return (n);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	char	*ss1;
	char	*ss2;
	char	*cpy;

	ss1 = s1;
	ss2 = s2;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), free(s2), NULL);
	cpy = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	free(ss1);
	free(ss2);
	return (cpy);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
		if (*s++ == ((char)c))
			return ((char *)--s);
	if ((char)c == 0)
		return ((char *)s);
	return (NULL);
}
