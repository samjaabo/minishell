/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/17 17:24:33 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_perror("getcwd");
		g_data.exit_status = 0;
		return ;
	}
	printf("%s\n", path);
	free(path);
	g_data.exit_status = 0;
}
