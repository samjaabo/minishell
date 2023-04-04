/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:35:03 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/20 10:44:10 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		n;

	n = ft_strlen(needle);
	if ((!haystack && len == 0) || *needle == '\0')
		return ((char *)haystack);
	while (*haystack && len >= n && len--)
		if (ft_strncmp(haystack++, needle, n) == 0)
			return ((char *)--haystack);
	return (NULL);
}
