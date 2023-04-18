/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:11:52 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/18 12:34:03 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	eliminate_dollar(char **str, int i)
{
	char	*expanded;
	int		j;

	expanded = malloc(ft_strlen(*str) * sizeof(char));
	if (!expanded)
		return ;
	j = 0;
	while (j < i)
	{
		expanded[j] = *(*str + j);
		j++;
	}
	while (*(*str + j + 1))
	{
		expanded[j] = *(*str + j + 1);
		j++;
	}
	expanded[j] = '\0';
	free(*str);
	*str = expanded;
}

/*----------------------------------------------------------------*/

static int	variable_len(char *str, int i, int *rest)
{
	int	j;

	j = 0;
	if (ft_isdigit(str[i + j + 1]) || str[i + j + 1] == '?')
		j = 1;
	else
	{
		while (str[i + j + 1])
		{
			if (!ft_isalnum(str[i + j + 1]))
				break ;
			j++;
		}
	}
	*rest = 0;
	while (str[i + j + *rest + 1])
		(*rest)++;
	return (j);
}

/*----------------------------------------------------------------*/

static int	expanding(char **str, char *var, t_str_len p)
{
	char	*var_expand;
	char	*str_expand;
	int		len;
	int		last;

	if (var[0] == '?')
		var_expand = ft_itoa(g_data.exit_status);
	else
		var_expand = get_env(var);
	if (!var_expand)
		len = 0;
	else
		len = ft_strlen(var_expand);
	str_expand = malloc((p.bef + p.aft + len + 1) * sizeof(char));
	if (!str_expand)
		return (0);
	ft_memcpy(str_expand, *str, p.bef);
	if (str_expand)
		ft_memcpy(str_expand + p.bef, var_expand, len);
	last = p.bef + p.var;
	ft_memcpy(str_expand + (p.bef + len), *str + last + 1, p.aft);
	str_expand[p.bef + p.aft + len] = '\0';
	free(*str);
	*str = str_expand;
	return (free(var_expand), len);
}

/*----------------------------------------------------------------*/

void	expand_variable(char **str, int *i)
{
	t_str_len	ptr;
	char		*var;
	int			len;

	ptr.bef = *i;
	ptr.var = variable_len(*str, *i, &ptr.aft);
	if (ptr.var)
	{
		var = malloc((ptr.var + 1) * sizeof(char));
		if (!var)
		{
			free(str);
			exit(EXIT_FAILURE);
		}
		ft_memcpy(var, *str + *i + 1, ptr.var);
		var[ptr.var] = '\0';
		len = expanding(str, var, ptr);
		if (len)
			*i += len - 1;
		free(var);
	}
	else
		*i += 1;
}
