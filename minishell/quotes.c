/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:23:39 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/01 12:19:31 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes_maker(t_token_list	**tokens,char *line)
{
	char	*word;

	word = malloc(to_alloc(line) + 1);

	int	i = 0;
	int j = 0;

	int	check;
	check  = 0;
	while(line[i])
	{
		if(line[i] == 39 && check == 0)
		{
			i++;
			check = 1;
		}
		if(line[i] != 39 )
		{
			word[j] = line[i] ;
			i++;
			j++;
		}
		
		if(line[i] == 39 && check == 1)
		{
			i++;
			break;
		}
	}
	word[j] = '\0';
	addback(tokens, word, WORD);
	// free(word);
	return(line + i);
}

char	*word_maker(t_token_list	**tokens,char *line)
{
	int	i = 0;
	char *word;
	while (!ft_strchr(" \t\v\f\r><$|\"\'", line[i]))
		{
			i++;
		}
	word = malloc((i + 1)*sizeof(char));
	i = 0;
	while (!ft_strchr(" \t\v\f\r><$|\"\'", line[i]))
		{
			word[i] = line[i];
			i++;
		}
		word[i] = '\0';
		addback(tokens, word, WORD);
		// free(word);
		return(line + i);
}