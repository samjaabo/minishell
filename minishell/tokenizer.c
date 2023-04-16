/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:20 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/15 16:10:11 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

// void free_node(t_token_list **tokens)
// {
// 	t_token_list *head;
// 	head = *tokens;
// 	if(!head->next)
// 		free_node(&head->next);
// 	free(head);
// }

t_token_list *tokenizer(char *line)
{
	t_token_list	*tokens;
	tokens = NULL;
	
    while (*line)
    {
		// printf("%s\n", line);
        if (ft_strchr(" \t\v\f\r", *line))
            line = is_wspace(&tokens, line);
        else if (ft_strchr("><", *line))
            line = is_redirections(&tokens, line);
        else if (ft_strchr("$|", *line))
            line = is_dollar_pipe(&tokens, line);
        else if (ft_strchr("\'", *line))
		{
			if(is_open_quote(line, '\'') < 2)
			{
				write(2, "\e[1;31m open quotes1!\n\e[0m", 27);
				ft_lstclear(&tokens);
				g_data.exit_status = 258;
				break;
			}	
			line = quotes_maker(&tokens, line);
		}
		else if (ft_strchr("\"", *line))
		{
			if(is_open_quote(line, '\"') < 2)
			{
				write(2, "\e[1;31m open quotes2!\n\e[0m", 27);
				ft_lstclear(&tokens);
				g_data.exit_status = 258;
				break;
			}
			line = is_dquote(&tokens, line);
			if (*line == '$')
				line = afdollar(&tokens, line);
		}
        else
		{
            line = word_maker(&tokens, line);
		}
    }
	return(tokens);
}
