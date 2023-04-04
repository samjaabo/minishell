/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:33:41 by samjaabo          #+#    #+#             */
/*   Updated: 2022/10/13 09:46:25 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*alloc;
	char			*str;
	unsigned int	i;

	if (!s)
		return (ft_strdup(""));
	else if (!f)
		return (ft_strdup(s));
	alloc = ft_strdup(s);
	str = alloc;
	if (!alloc)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = f(i, str[i]);
		++i;
	}
	return (alloc);
}
