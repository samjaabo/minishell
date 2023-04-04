/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:25:26 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 15:04:52 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	n;

// 	n = 0;
// 	while (s && *s++)
// 		++n;
// 	return (n);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	char	*ss1;
	char	*ss2;
	char	*cpy;

	ss1 = s1;
	ss2 = s2;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (res == NULL)
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

// char	*ft_strchr(const char *s, int c)
// {
// 	if (s == NULL)
// 		return (NULL);
// 	while (*s)
// 		if (*s++ == ((char)c))
// 			return ((char *)--s);
// 	if ((char)c == 0)
// 		return ((char *)s);
// 	return (NULL);
// }
