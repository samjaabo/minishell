/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:06:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 18:59:04 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_data	g_data;

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
	errno = 0;
	g_data.exit_status = GENERAL_ERROR;
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
	errno = 0;
	g_data.exit_status = GENERAL_ERROR;
}

static int	ft_dup_default_stdio(void)
{
	g_data.new_stdin = dup(STDIN_FILENO);
	if (g_data.new_stdin < 0)
		return (ERROR);
	g_data.new_stdout = dup(STDOUT_FILENO);
	if (g_data.new_stdout < 0)
		return (ERROR);
	return (SUCCESS);
}

void	ft_init(char **env)
{
	char	*path;

	(void)env;
	if (ft_copy_env(env) != SUCCESS)
		exit(1);
	ft_update_prompt_string();
	ft_dup_default_stdio();
	ft_shell_level();
	path = getcwd(NULL, 0);
	if (!path)
		ft_perror("shell-init: error retrieving current directory:"
			" getcwd: cannot access parent directories");
	free(path);
	ft_init_env();
}

void	ft_update_prompt_string(void)
{
	char	*path;
	char	*succ;
	char	*fail;

	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("minishell:");
	if (ft_strrchr(path, '/'))
	{
		fail = ft_strjoin3("", ft_strrchr(path, '/'), "$ ");
		succ = ft_strjoin3("", ft_strrchr(path, '/'), "$ ");
	}
	else
	{
		fail = ft_strjoin3("", path, "$ ");
		succ = ft_strjoin3("", path, "$ ");
	}
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
	ft_clear(g_data.env);
	ft_pwd(2);
	exit(g_data.exit_status);
}

int	ft_copy_env(char **env)
{
	int		i;
	char	**arr;

	i = 0;
	while (env && env[i])
	{
		arr = ft_realloc(g_data.env, ft_strdup(env[i]));
		if (!arr)
			return (ft_clear(g_data.env), g_data.env = NULL, ERROR);
		g_data.env = arr;
		++i;
	}
	return (SUCCESS);
}
