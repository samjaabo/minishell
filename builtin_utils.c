/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 21:37:30 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error_not_valid(char *str)
{
	write(2, "minishell: export: ", 19);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	g_data.exit_status = GENERAL_ERROR;
}

int	ft_isnot_valid_identifier(char *str, char stop)
{
	int			i;
	static int	status;

	if (!str && !stop)
		return (i = status, status = SUCCESS, i);
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		status = GENERAL_ERROR;
		return (ft_error_not_valid(str), ERROR);
	}
	i = 0;
	while (str[i] && str[i] != stop)
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
		{
			status = GENERAL_ERROR;
			return (ft_error_not_valid(str), ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

int	ft_return_default_stdio(void)
{
	if (dup2(g_data.new_stdin, STDIN_FILENO) < 0)
		return (ERROR);
	if (dup2(g_data.new_stdout, STDOUT_FILENO) < 0)
		return (ERROR);
	return (SUCCESS);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
