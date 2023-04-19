/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:37:54 by araqioui          #+#    #+#             */
/*   Updated: 2023/04/19 20:30:44 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



/*----------------------------------------------------------------*/

void	fill_array(char *str, char **new, int i, int j)
{
	int	qu;

	while (str[i])
	{
		while (str[i] && str[i] != '$' && str[i] != 34 && str[i] != 39)
			*(*new + j++) = str[i++];
		if (str[i] == '$')
		{
			*(*new + j++) = '"';
			*(*new + j++) = str[i++];
			while (ft_isalnum(str[i]))
				*(*new + j++) = str[i++];
			*(*new + j++) = '"';
		}
		if (str[i] == 34 || str[i] == 39)
		{
			qu = str[i];
			*(*new + j++) = str[i++];
			while (str[i] && str[i] != qu)
				*(*new + j++) = str[i++];
			*(*new + j++) = str[i++];
		}
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
static int	check_var_quotes(char *str, int *qu)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (qu)
		*qu = 0;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (qu)
				*qu = 1;
			i++;
			while (str[i] && str[i] != 39 && str[i] != 34)
					i++;
			i++;
		}
		if (str[i] == 36 && (ft_isalpha(str[i + 1]) || str[i + 1] == 95))
			j++;
	}
	return (j);
}

/*----------------------------------------------------------------*/

void	fill_args(t_cmd **ptr, char **str)
{
	int	j;

	j = check_var_quotes(*str, 0);
	if (j)
		put_quotes(str, j);
	find_variable(str, 0);
	*str = rm_quote(str, 0, 0);
	if (!(*ptr)->args)
		(*ptr)->args = ft_split(*str, ' ');
	else
		(*ptr)->args = ft_realloc((*ptr)->args, ft_strdup(*str));
}

/*----------------------------------------------------------------*/

void    fill_the_list(t_cmd **lst, char **str, int i, int j)
{
    t_cmd    *ptr;
    int        qu;

    ptr = *lst;
    while (ptr)
    {
        while (str[i] && str[i][0] != 124)
        {
            if (str[i][0] == '<' || str[i][0] == '>')
            {
                j = check_var_quotes(str[i + 1], &qu);
                if (!(str[i][0] == '<' && str[i][0] == str[i][1] && !str[i][2]))
                {
                    if (j)
                        put_quotes(&str[i + 1], j);
                    find_variable(&str[i + 1], 0);
                }
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
