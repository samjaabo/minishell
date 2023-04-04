/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:55 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/29 15:59:46 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*alloc;
	int		n;
	size_t	sz;

	if (!s)
		return (NULL);
	n = 0;
	sz = ft_strlen(s);
	if (start > sz)
		return (ft_strdup(""));
	alloc = (char *)s + start;
	while (*alloc++ && len--)
		++n;
	alloc = (char *)ft_calloc(n + 1, sizeof(char));
	if (!alloc)
		return (NULL);
	(void)ft_strlcpy(alloc, s + start, n + 1);
	return (alloc);
}
