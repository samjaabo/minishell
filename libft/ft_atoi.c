/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:49:24 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 19:05:46 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	const char			*s;
	unsigned long long	res;
	int					sign;

	sign = 1;
	s = str;
	while (*s == ' ' || *s == '\n' || *s == '\t'
		|| *s == '\r' || *s == '\v' || *s == '\f')
		++s;
	if (*s == '-' && ++s)
		sign = -1;
	else if (*s == '+')
		++s;
	res = 0;
	while (ft_isdigit(*s))
	{
		res = (res * 10) + (*s++ - '0');
		if ((sign == 1 && res > 9223372036854775807LLU)
			|| (sign == -1 && res > 9223372036854775808LLU))
		{
			return (9223372036854775807);
		}
	}
	return ((long long)(res * sign));
}
