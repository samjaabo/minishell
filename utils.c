/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:06:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/13 23:50:44 by samjaabo         ###   ########.fr       */
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

void	ft_init(char **env)
{
	if (ft_copy_env(env) != SUCCESS)
		exit(1);
	ft_update_prompt_string();
	g_data.here_doc = NULL;
	system("clear");
	ft_dup_default_stdio();
}

void	ft_update_prompt_string(void)
{
	char	*path;
	char	*succ;
	char	*fail;

	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("minishell: ");
	fail = ft_strjoin3("\e[1;91m\u2794\e[0m \e[1;94m", ft_strrchr(path, '/'), "\e[0m ");
	succ = ft_strjoin3("\e[1;32m\u2794\e[0m \e[1;94m", ft_strrchr(path, '/'), "\e[0m ");
	free(g_data.succ_str);
	free(g_data.fail_str);
	free(path);
	g_data.succ_str = succ;
	g_data.fail_str = fail;
	if (!succ || !fail || !path)
	{
		g_data.fail_str = NULL;
		g_data.succ_str = NULL;
		ft_perror("malloc");
	}
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

// int	ft_realloc_fd(int new)
// {
// 	int		count;
// 	int		*ints;
// 	int		*arcpy;
// 	int		*cpy;

// 	count = 0;
// 	while (g_data.here_doc && g_data.here_doc[count] != -1)
// 		count++;
// 	ints = ft_calloc((count + 2), sizeof(int));
// 	if (!ints)
// 		return (free(g_data.here_doc), ft_perror("malloc"), ERROR);
// 	cpy = ints;
// 	arcpy = g_data.here_doc;
// 	while (g_data.here_doc && *g_data.here_doc != -1)
// 		*ints++ = *g_data.here_doc++;
// 	*ints++ = new;
// 	*ints = -1;
// 	free(arcpy);
// 	return (SUCCESS);
// }

// int	ft_close_fds(void)
// {
// 	int	i;
// 	int ret;

// 	i = 0;
// 	ret = SUCCESS;
// 	while (g_data.here_doc[i] != -1)
// 		ret = close(g_data.here_doc[i++]);
// 	free(g_data.here_doc);
// 	g_data.here_doc = NULL;
// 	return (ret);
// }

// int    main(int ac, char **av, char **env)
// {
//     char **envy;
//     int i = 0;
//     char *s;

//     while (env[i])
//         i++;
//     envy = malloc((i + 1) * sizeof(char *));
//     int j = 0;
//     while (env[j])
//     {
//         s = ft_strdup(env[j]);
//         envy[j] = s;
//         j++;
//     }
//     envy[j + 1] = 0;

// }

int	ft_copy_env(char **env)
{
	int		i;
	char	**arr;

	i = 0;
	while (env[i])
	{
		arr = ft_realloc(g_data.env, ft_strdup(env[i]));
		if (!arr)
			return (ft_clear(g_data.env), g_data.env = NULL, ERROR);
		g_data.env = arr;
		++i;
	}
	return (SUCCESS);
}
