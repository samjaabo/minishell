/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:48 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/26 09:27:01 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinstr(char const *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*alloc;
	size_t	n;

	if (!s1)
		return (NULL);
	start = (char *)s1;
	end = ft_strchr(s1, '\0');
	end--;
	n = 0;
	while (isinstr(set, *start) && *start++)
		++n;
	while (start < end && isinstr(set, *end--))
		++n;
	n = ft_strlen(s1) - n + 1;
	alloc = (char *)ft_calloc(n, sizeof(char));
	if (!alloc)
		return (NULL);
	(void)ft_strlcpy(alloc, start, n);
	return (alloc);
}
