/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 10:37:03 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/29 13:09:41 by samjaabo         ###   ########.fr       */
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
