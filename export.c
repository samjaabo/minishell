/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:28:17 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_table(int *len)
{
	char	**envp;
	int		i;

	*len = 0;
	while (g_data.env[*len])
		(*len)++;
	envp = malloc((*len + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	envp[*len] = NULL;
	i = -1;
	while (g_data.env[++i])
		envp[i] = ft_strdup(g_data.env[i]);
	return (envp);
}

/*----------------------------------------------------------------*/

static void	ft_print_env(char **envp, int i)
{
	int	j;
	int	flag;

	flag = 0;
	j = 0;
	while (envp[i][j] && envp[i][j] != '=')
		write(1, &envp[i][j++], 1);
	if (envp[i][j] == '=')
	{
		write(1, &envp[i][j++], 1);
		flag = write(1, "\"", 1);
	}
	while (envp[i][j])
		write(1, &envp[i][j++], 1);
	if (!envp[i][j] && flag)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

void	selection_sort_vars(void)
{
	char	**envp;
	int		len;
	int		i;

	len = 0;
	envp = fill_table(&len);
	if (!envp)
		return ;
	selection_sort(envp, len);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && g_data.default_path)
			continue ;
		if (!ft_strncmp(envp[i], "_=", 2))
			continue ;
		ft_print_env(envp, i);
	}
	ft_clear(envp);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	char	*ss;
	size_t	len;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (str);
	ss = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	while (s3 && *s3)
		*str++ = *s3++;
	*str = 0;
	return (ss);
}
