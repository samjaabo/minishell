/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:45:55 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/13 22:18:06 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern t_data	g_data;

void	ft_cd(char *s)
{
	if (!s)
		return ;
	if (chdir(s) < 0)
	{
		g_data.exit_status = -1;
		ft_perror(s);
		return ;
	}
	g_data.exit_status = 0;
	ft_update_prompt_string();
}
