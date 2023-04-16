/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:34 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/15 16:14:14 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_data	g_data;

void	print_error(t_token_list **tokens)
{
	write(2, "parse error\n", 13);
	ft_lstclear(tokens);
	g_data.exit_status = 258;
}

void    syntax_red(t_token_list **tokens)
{
    t_token_list	*t_tokens;

	t_tokens = *tokens;
	if(t_tokens)
	{
		if ((t_tokens->value[0] == '>' || t_tokens->value[0] == '<') 
			&& !t_tokens->next ) // ila kan bo7do
		{
			return (print_error(tokens));
			return ;
		}
		while (t_tokens)
		{
			if (t_tokens->value[0] && (t_tokens->value[ft_strlen(t_tokens->value) - 1] == '>'
				|| t_tokens->value[ft_strlen(t_tokens->value) - 1] == '<')
			&& !t_tokens->next) // ila kan f lakher
			{
				print_error(tokens);
				return ;
			}
			else if ((t_tokens->next) && (t_tokens->value[0] == '>' || t_tokens->value[0] == '<')
			&& t_tokens->next->value[0] == 32) // >> >
			{
				if (t_tokens->next->next->value[0] == '>' || t_tokens->next->next->value[0] == '<')
				{
					print_error(tokens);
					return ;
				}
				else if (t_tokens->next->next->value[0] == '|')
				{
					print_error(tokens);
					return ;
				}
			}
			else if(t_tokens->value[0] == '>' && t_tokens->value[1] == '>' 
				&& t_tokens->next->value[0] == '>' ) // >>>
			{
				print_error(tokens);
				return ;
			}
			else if(t_tokens->value[0] == '<' && t_tokens->value[1] == '<' 
				&& t_tokens->next->value[0] == '<' ) // >>>
			{
				print_error(tokens);
				return ;
			}
			else if ((t_tokens->value[0] == '>' && t_tokens->next->value[0] == '<') 
					|| (t_tokens->value[0] == '<' && t_tokens->next->value[0] == '>'))
			{
				print_error(tokens);
				return ;
			}
			t_tokens = t_tokens->next;
		}
	}
}

void    syntax_pipe(t_token_list **tokens)
{
	t_token_list	*t_tokens;
	
	t_tokens = *tokens;
	if (!*tokens)
		return ;
	if (t_tokens->value[0] == '|')
	{
		print_error(tokens);
		return ;
	}
	while(t_tokens->next)
	{
		if (t_tokens->value[0] == '|' && !t_tokens->next)
		{
			print_error(tokens);
			return ;
		}
		else if (t_tokens->value[0] == '|' && t_tokens->next->value[0] == '|')
		{
			print_error(tokens);
			return ;
		}
		if(t_tokens->next->next)
		{
		if (t_tokens->value[0] == '|' && t_tokens->next->value[0] == 32 
				&& t_tokens->next->next->value[0] == '|')
		{
			print_error(tokens);
			return ;		
		}
		}
		t_tokens = t_tokens->next;
	}
}