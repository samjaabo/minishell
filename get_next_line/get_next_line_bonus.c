/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:30:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 21:54:19 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*split_data(char *data, char **_line)
{
	char	*line;
	char	*left;
	char	*dt;
	char	*tmp;

	dt = data;
	while (*dt && *dt++ != '\n')
		;
	line = malloc(ft_strlen(data) - ft_strlen(dt) + 1);
	left = malloc(ft_strlen(dt) + 1);
	if (!left || !line)
		return (free(line), free(left), free(data), NULL);
	*_line = line;
	tmp = left;
	while (*dt)
		*left++ = *dt++;
	*left = '\0';
	dt = data;
	while (*dt && *dt != '\n')
		*line++ = *dt++;
	if (*dt == '\n')
		*line++ = '\n';
	*line = '\0';
	return (free(data), tmp);
}

static char	*ft_read(int fd)
{
	char		*buff;
	char		*data;
	int			nbytes;

	data = NULL;
	while (!ft_strchr(data, '\n'))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return (data);
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes <= 0)
			return (free(buff), data);
		buff[nbytes] = 0;
		data = ft_strjoin(data, buff);
		if (!data)
			return (data);
	}
	return (data);
}

static void	ft_clear(char **data)
{
	int	n;

	n = 0;
	while (n < 10240)
	{
		if (data[n])
		{
			free(data[n]);
			data[n] = NULL;
		}
		++n;
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*data[10240];

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (ft_clear(data), NULL);
	if (read(fd, 0, 0) < 0)
		return (free(data[fd]), data[fd] = NULL);
	if (!ft_strchr(data[fd], '\n'))
	{
		line = ft_read(fd);
		if (!line && !data[fd])
			return (NULL);
		if (!line && data[fd][0] == '\0')
			return (free(data[fd]), data[fd] = NULL);
		data[fd] = ft_strjoin(data[fd], line);
		if (!data[fd])
			return (NULL);
	}
	data[fd] = split_data(data[fd], &line);
	if (!data[fd])
		return (NULL);
	if (*line == '\0' && data[fd][0] == '\0')
		return (free(data[fd]), free(line), data[fd] = NULL);
	return (line);
}
