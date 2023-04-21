/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:06:54 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

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

	succ = NULL;
	fail = NULL;
	path = getcwd(NULL, 0);
	if (!path)
		path = ft_strdup("/minishell:");
	if (path && ft_strrchr(path, '/'))
	{
		fail = ft_strjoin3("", ft_strrchr(path, '/') + 1, "$ ");
		succ = ft_strjoin3("", ft_strrchr(path, '/') + 1, "$ ");
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
