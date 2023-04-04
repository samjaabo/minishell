/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:48:02 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/31 17:24:39 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst > src)
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
