/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:06:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:08 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "header.h"

extern t_data g_data;

void ft_printar(char **t)
{
	if (!t)
	{
		printf("(null)");
		return ;
	}
	while(*t)
		printf(">%s<\n", *t++);
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

void	ft_perror(const char *msg)
{
	if (!msg)
		return ;
	write(2, "minishell: ", 12);
	perror(msg);
}

void	ft_error(const char *cmd, const char *msg)
{
	if (!msg)
		return ;
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

// int	ft_istty(void)
// {
// 	if (!isatty(STDIN_FILENO))
// 		return (ft_error("STDIN", "Is not a terminal"), 0);
// 	if (!isatty(STDOUT_FILENO))
// 		return (ft_error("STDOUT", "Is not a terminal"), 0);
// 	if (!isatty(STDERR_FILENO))
// 		return (ft_error("STDERR", "Is not a terminal"), 0);
// 	return (1);
// }
static int	ft_dup_default_stdio(void)
{
	if ((g_data.new_stdin=dup(STDIN_FILENO)) < 0)
		return (ERROR);
	if ((g_data.new_stdout=dup(STDOUT_FILENO)) < 0)
		return (ERROR);
	if ((g_data.new_stderr=dup(STDERR_FILENO)) < 0)
		return (ERROR);
	return (SUCCESS);
}

void	ft_init(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_perror("malloc");
		exit(1);
	}
	g_data.fail_str = ft_strjoin3("\e[1;91m\u2794\e[0m \e[1;94m", ft_strrchr(path, '/'), "\e[0m ");
	g_data.succ_str = ft_strjoin3("\e[1;32m\u2794\e[0m \e[1;94m", ft_strrchr(path, '/'), "\e[0m ");
	free(path);
	if (!g_data.succ_str || !g_data.fail_str)
	{
		free(g_data.fail_str);
		free(g_data.succ_str);
		ft_perror("malloc");
		exit(1);
	}
	g_data.here_doc = NULL;
	system("clear");
	ft_dup_default_stdio();
}

void	ft_exit(void)
{
	free(g_data.succ_str);
	free(g_data.fail_str);
	close(g_data.new_stdin);
	close(g_data.new_stdout);
	close(g_data.new_stderr);
	exit(g_data.exit_status);
}

int	ft_realloc_fd(int new)
{
	int		count;
	int		*ints;
	int		*arcpy;
	int		*cpy;

	count = 0;
	while (g_data.here_doc && g_data.here_doc[count] != -1)
		count++;
	ints = ft_calloc((count + 2), sizeof(int));
	if (!ints)
		return (free(g_data.here_doc), ft_perror("malloc"), ERROR);
	cpy = ints;
	arcpy = g_data.here_doc;
	while (g_data.here_doc && *g_data.here_doc != -1)
		*ints++ = *g_data.here_doc++;
	*ints++ = new;
	*ints = -1;
	free(arcpy);
	return (SUCCESS);
}

int	ft_close_fds(void)
{
	int	i;
	int ret;

	i = 0;
	ret = SUCCESS;
	while (g_data.here_doc[i] != -1)
		ret = close(g_data.here_doc[i++]);
	free(g_data.here_doc);
	g_data.here_doc = NULL;
	return (ret);
}