/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finals_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 00:07:54 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/15 16:03:04 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	finals_m(t_token_list	*tokens, t_token_list	**finals)
{
	char	*c;

	c = NULL;
	if (!tokens)
		return;

	while(tokens->next)
	{
		if (tokens->type == WORD)
				c = ft_strjoin(c, tokens->value);
		else if (tokens->type == PIPE)
			{
				if (c)
					addback(finals, c, WORD);
				addback(finals, tokens->value, PIPE);
				c = NULL;
			}
		else if (tokens->type == HEREDOC)
			{
				if (c)
					addback(finals, c, WORD);
				addback(finals, tokens->value, HEREDOC);
				c = NULL;
			}
		else if (tokens->type == RIGHTRED)
			{
				if (c)
					addback(finals, c, WORD);
				addback(finals, tokens->value, RIGHTRED);
				c = NULL;
			}
		else if (tokens->type == LEFTRED)
			{
				if (c)
					addback(finals, c, WORD);
				addback(finals, tokens->value, LEFTRED);
				c = NULL;
			}
		else if (tokens->type == APPEND)
			{
				if (c)
					addback(finals, c, WORD);
				addback(finals, tokens->value, APPEND);
				c = NULL;
			}
		else if (tokens->type == SPACE)
			{
				if (c)
					addback(finals, c, WORD);
				c = NULL;
			}
		tokens = tokens->next;
	}
	if (tokens->type != PIPE)
	{	
		c = ft_strjoin(c, tokens->value);
		addback(finals, c, tokens->type);
	}
	if (tokens->type == PIPE)
	{	if(c)
			addback(finals, c, WORD);
		write(2, "parse error\n", 13);
		ft_lstclear(finals);
	}
}