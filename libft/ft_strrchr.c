/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:37:03 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/19 13:48:48 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = ft_strchr(s, '\0');
	if ((char)c == '\0')
		return (str);
	while (str-- > s)
		if (*str == (char)c)
			return (str);
	return (NULL);
}
