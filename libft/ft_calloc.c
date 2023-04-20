/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:40:34 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 19:52:15 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long long	sz;
	void				*data;

	sz = count * size;
	data = malloc((size_t)sz);
	if (!data)
		return (NULL);
	(void)ft_memset(data, 0, (size_t)sz);
	return (data);
}
