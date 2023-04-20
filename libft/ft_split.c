/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:51:46 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 19:54:50 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc(char **array, char *new)
{
	int		count;
	char	**strs;
	char	**arcpy;
	char	**cpy;

	if (!new)
		return (ft_perror("malloc"), NULL);
	count = 0;
	while (array && array[count])
		count++;
	strs = malloc((count + 2) * sizeof(char *));
	if (!strs)
		return (ft_perror("malloc"), NULL);
	cpy = strs;
	arcpy = array;
	while (array && *array)
		*strs++ = *array++;
	*strs++ = new;
	*strs = NULL;
	free(arcpy);
	return (cpy);
}

char	*ft_reallco_str(char *oldstr, char new)
{
	char	*s;
	char	*ss;
	char	*old;
	int		len;

	old = oldstr;
	if (!oldstr)
		return (NULL);
	len = ft_strlen(oldstr);
	s = malloc(len + 2);
	if (!s)
		return (NULL);
	ss = s;
	while (oldstr && *oldstr)
		*ss++ = *oldstr++;
	*ss++ = new;
	*ss = 0;
	free(old);
	return (s);
}

char	**ft_split(const char *str, char c)
{
	char	**args;
	char	*buf;
	int		i;

	buf = ft_strdup("");
	args = NULL;
	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == c)
		{
			while (str[i] == c)
				++i;
			if (buf[0] != 0)
			{
				args = ft_realloc(args, buf);
				buf = ft_strdup("");
			}
		}
		else
			buf = ft_reallco_str(buf, str[i++]);
	}
	if (buf[0] != 0)
		return (ft_realloc(args, buf));
	return (free(buf), args);
}
