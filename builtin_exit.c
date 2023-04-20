/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:11:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/20 20:06:04 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_builtin_error(char *cmd, char *arg, char *err)
{
	write(2, "minishell: ", 13);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 3);
	write(2, err, ft_strlen(err));
	write(2, "\n", 2);
	g_data.exit_status = EXIT_CODE_OUT_RANGE;
}

int	ft_check_args(char **args)
{
	int	i;

	i = 0;
	while (args[1][i] == ' ')
		++i;
	if (args[1][i] == '-')
		++i;
	while (ft_isdigit(args[1][i]))
		++i;
	if (args[1] && args[2] && args[1][i] == 0)
		return (ft_error(args[0], "too many arguments"), 0);
	if (args[1][i] != 0)
	{
		ft_builtin_error(args[0], args[1], "numeric argument required");
		g_data.exit_status = EXIT_CODE_OUT_RANGE;
		return (0);
	}
	return (1);
}

void	ft_builtin_exit(char **args, t_cmd **cmd)
{
	int	i;

	if (!args)
		return ;
	if (!args[1])
	{
		ftx_lstclear(cmd);
		ft_exit();
	}
	g_data.exit_status = SUCCESS;
	if (ft_check_args(args))
	{
		i = 0;
		while (args[1][i] == ' ')
			++i;
		if (!strcmp(&args[1][i], "9223372036854775807"))
			g_data.exit_status = (int)9223372036854775807;
		else if (ft_atoi(args[1]) == 9223372036854775807)
			ft_builtin_error(args[0], args[1], "numeric argument required");
		else
			g_data.exit_status = (int)ft_atoi(args[1]);
	}
	ftx_lstclear(cmd);
	ft_exit();
}
