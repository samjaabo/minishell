/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:27:50 by byoussef          #+#    #+#             */
/*   Updated: 2023/03/27 14:00:26 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup( char *s1)
{
	int		i;
	char	*p;

	i = ft_strlen(s1);
	p = malloc((i + 1) * sizeof(char));
	if (!p)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src == dst)
		return (dst);
	if (!src && !dst)
		return (0);
	while (i < n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}
