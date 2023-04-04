/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:59:24 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 17:00:07 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *str)
{
	size_t		len;
	char		*cpy;
	char		*s;

	//printf("dup = %s\n", str);
	len = ft_strlen(str);
	s = (char *)malloc(len * sizeof(char) + 1);
	if (!s)
		return (NULL);
	cpy = s;
	while (*str)
		*cpy++ = *str++;
	*cpy = '\0';
	return (s);
}