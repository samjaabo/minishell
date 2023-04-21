/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:44:56 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 02:57:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_new_line(char **args, int *i)
{
	int		new_line;
	int		o;

	new_line = 1;
	while (args && args[*i] && !ft_strncmp(args[*i], "-n", 2))
	{
		o = 2;
		while (args[*i][o] == 'n')
			++o;
		if (args[*i][o] != 0)
			break ;
		new_line = 0;
		(*i)++;
	}
	return (new_line);
}

void	ft_echo(char **args)
{
	int		i;
	int		new_line;

	if (!args || !args[0])
		return ;
	i = 1;
	new_line = ft_echo_new_line(args, &i);
	while (args && args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		++i;
	}
	if (new_line)
		write(1, "\n", 1);
	g_data.exit_status = SUCCESS;
}
