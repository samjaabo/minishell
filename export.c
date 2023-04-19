/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:28:17 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/19 17:47:36 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**fill_table(int *len)
{
	char	**envp;
	int		i;

	*len = 0;
	while (g_data.env[*len])
		(*len)++;
	envp = malloc((*len + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	envp[*len] = NULL;
	i = -1;
	while (g_data.env[++i])
		envp[i] = ft_strdup(g_data.env[i]);
	return (envp);
}

/*----------------------------------------------------------------*/

void	selection_sort_vars(void)
{
	char	**envp;
	int		len;
	int		i;
	int		j;
	int		flag;

	len = 0;
	envp = fill_table(&len);
	if (!envp)
		return ;
	selection_sort(envp, len);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5) && g_data.default_path)
			continue ;
		if (!ft_strncmp(envp[i], "_=", 2))
			continue ;
		flag = 0;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			write(1, &envp[i][j++], 1);
		if (envp[i][j] == '=')
		{
			write(1, &envp[i][j++], 1);
			flag = write(1, "\"", 1);
		}
		while (envp[i][j])
			write(1, &envp[i][j++], 1);
		if (!envp[i][j] && flag)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	ft_clear(envp);
}

/*----------------------------------------------------------------*/

// static char	*get_the_var(char *str)
// {
// 	char	*var;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	var = malloc((i + 1) * sizeof(char));
// 	if (!var)
// 		return (NULL);
// 	var[i] = '\0';
// 	j = -1;
// 	while (++j < i)
// 		var[j] = str[j];
// 	return (var);
// }

/*----------------------------------------------------------------*/



/*----------------------------------------------------------------*/

// void	export(char **args)
// {
// 	int		i;

// 	if (args[1])
// 	{
// 		i = 0;
// 		while (args[++i])
// 		{
// 			if (valid_var(args[i]))
// 				mod_vars(args[i]);
// 			else
// 				printf("error: %s: not a valid identifier\n", args[i]);
// 		}
// 	}
// 	else
// 		selection_sort_vars();
// }
