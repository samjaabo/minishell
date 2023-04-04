/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:20:19 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/20 10:44:58 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*by;
	unsigned char	chr;

	by = (unsigned char *)s;
	chr = (unsigned char)c;
	while (n--)
		if (*by++ == chr)
			return (--by);
	return (NULL);
}
