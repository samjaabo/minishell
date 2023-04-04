/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:20 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/03 12:17:08 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

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
				printf("\e[1;31m open quotes1!\n \e[0m");
				ft_lstclear(&tokens);
				break;
			}	
			line = quotes_maker(&tokens, line);
		}
		else if (ft_strchr("\"", *line))
		{
			if(is_open_quote(line, '\"') < 2)
			{
				printf("\e[1;31m open quotes2!\n \e[0m");
				ft_lstclear(&tokens);
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
