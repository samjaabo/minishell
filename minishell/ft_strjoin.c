/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:55:51 by byoussef          #+#    #+#             */
/*   Updated: 2023/03/27 13:59:15 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*p;
	size_t	ls1;
	size_t	ls2;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = malloc((ls1 + ls2 + 1) * sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s1, ls1);
	ft_memcpy(p + ls1, s2, ls2);
	p[ls1 + ls2] = '\0';
	return (p);
}
