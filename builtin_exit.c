/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:11:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/17 17:24:19 by samjaabo         ###   ########.fr       */
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

void	ft_builtin_exit(char **args)
{
	int	i;

	if (!args)
		return ;
	if (!args[1])
		ft_exit();
	g_data.exit_status = SUCCESS;
	i = 0;
	while (args[1][i] == ' ')
		++i;
	if (args[1][i] == '-')
		++i;
	while (ft_isdigit(args[1][i]))
		++i;
	if (args[1] && args[2] && args[1][i] == 0)
		return (ft_error(args[0], "too many arguments"));
	if (args[1][i] != 0)
	{
		ft_builtin_error(args[0], args[1], "numeric argument required");
		g_data.exit_status = EXIT_CODE_OUT_RANGE;
	}
	else
		g_data.exit_status = ft_atoi(args[1]);
	ft_exit();
}