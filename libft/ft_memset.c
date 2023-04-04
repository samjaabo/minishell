/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:10:10 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/20 12:55:50 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*by;
	unsigned char	chr;

	by = (unsigned char *)b;
	chr = (unsigned char)c;
	while (len--)
		*by++ = chr;
	return (b);
}
