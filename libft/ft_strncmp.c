/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:42:48 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/22 17:40:48 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*s11 && *s22 && --n)
		if (*s11++ != *s22++)
			return (*--s11 - *--s22);
	return (*s11 - *s22);
}
