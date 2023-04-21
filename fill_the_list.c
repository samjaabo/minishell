/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:37:54 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/21 14:14:41 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_bet_quotes(char *str, char **new, int *i, int *j)
{
	int	qu;

	qu = str[*i];
	*(*new + (*j)++) = str[(*i)++];
	while (str[*i] && str[*i] != qu)
		*(*new + (*j)++) = str[(*i)++];
	*(*new + (*j)++) = str[(*i)++];
}

/*----------------------------------------------------------------*/

void	fill_array(char *str, char **new, int i, int j)
{
	while (str[i])
	{
		while (str[i] && str[i] != '$' && str[i] != 34 && str[i] != 39)
			*(*new + j++) = str[i++];
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			*(*new + j++) = '"';
			*(*new + j++) = str[i++];
			while (ft_isalnum(str[i]))
				*(*new + j++) = str[i++];
			*(*new + j++) = '"';
		}
		else if (str[i] == '$')
		{
			*(*new + j++) = str[i++];
			*(*new + j++) = str[i++];
		}
		if (str[i] == 34 || str[i] == 39)
			fill_bet_quotes(str, new, &i, &j);
	}
	*(*new + j) = '\0';
}

/*----------------------------------------------------------------*/

void	put_quotes(char **str, int nb_q)
{
	char	*new;

	new = malloc((ft_strlen(*str) + nb_q * 2 + 1) * sizeof(char));
	if (!new)
		return ;
	fill_array(*str, &new, 0, 0);
	free(*str);
	*str = new;
}

/*----------------------------------------------------------------*/

static void	expand_files(char *str1, char **str, int check)
{
	if (!(str1[0] == '<' && str1[0] == str1[1] && !str1[2]))
	{
		if (check)
			put_quotes(str, check);
		find_variable(str, 0, 0);
	}
	else
		var_special_case(str);
}

/*----------------------------------------------------------------*/

void	fill_the_list(t_cmd **lst, char **str, int i, int j)
{
	t_cmd	*ptr;
	int		qu;

	ptr = *lst;
	while (ptr)
	{
		while (str[i] && str[i][0] != 124)
		{
			if (str[i][0] == '<' || str[i][0] == '>')
			{
				j = check_var_quotes(str[i + 1], &qu);
				expand_files(str[i], &str[i + 1], j);
				str[i + 1] = rm_quote(&str[i + 1], 0, 0);
				classing_files(&ptr, str[i], qu);
				ptr->redirs = ft_realloc(ptr->redirs, ft_strdup(str[++i]));
			}
			else
				fill_args(&ptr, &str[i]);
			i++;
		}
		i++;
		ptr = ptr->next;
	}
}
