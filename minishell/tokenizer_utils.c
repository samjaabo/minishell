/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:44:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/03 15:41:04 by byoussef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_redirections(t_token_list **tokens, char *line)
{
    if (*line == '>')
    {	
        if (*(line + 1) == '>')
        {
            addback(tokens, ">>", APPEND);
            return (line + 2);
        }
        addback(tokens, ">", RIGHTRED);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            addback(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        addback(tokens, "<", LEFTRED);
    }
	return (line + 1);
}

char    *is_wspace(t_token_list **tokens, char *line)
{
    int i;
    i = 0;
    while (ft_strchr(" \t\v\f\r", line[i]) && line[i])
        i++;
    addback(tokens, " ", SPACE);
    return (line + i);
}

char    *is_dollar_pipe(t_token_list **tokens, char *line)
{
    if(*line == '$')
    {
        addback(tokens,"$", DOLLAR);
        return (line + 1);
    }
    else if(*line == '|')
    {
        addback(tokens,"|", PIPE);
        return (line + 1);
    }
	return (0);
}

char    *is_word(t_token_list **tokens, char *line)
{
    int		i;
    char    *word;
	
    i = 0;
    while (!ft_strchr(" \t\v\f\r><$|\"\'", line[i]))
        i++;
	word = malloc((i + 1) * sizeof(char));
	int	j = 0;
	while (!ft_strchr(" \t\v\f\r><$|\"\'", line[j]))
	{
		word[j] = line[j];
		j++;
	}
	word[j] = '\0';
	// printf("|%s|\n", line);
	addback(tokens, word, WORD);
	// free(word);
	return (line + i);
}

int is_open_quote(char *line, char quote)
{
    int i;
    int x;

    i = 0 ;
    x = 0;
    while(line[i])
    {
        if(line[i] == quote)
            x++;
        i++;
    }
	// printf("%c\n", quote);
	// printf("%d\n", x);
    return (x);
}

int to_alloc(char *line)
{
    int i;
	int	j = 0;
    // int count;
    int flag;
    char quote ;
    i = 0;
    flag = 0;
    while (line[i])
    {
		if((line[i] == 39 || line[i] == 34) && flag == 0)
        {
            quote = line[i];
            flag = 1;
            i++;
        }
        if(line[i] != quote && flag  == 1)
        {
            i++;
			j++;
        }
        if(line[i] == quote && flag == 1)
		{
			i++;
            break;
		}
        if (line[i] == '$')
            break ;
    }
	return (j);
}

char    *is_squote(t_token_list **tokens, char *line, int *open)
{
    int i;
    int j;
    int count;
    int flag;
    char    *word;

    i = 0;
    j = 0;
	// open = 0;
	
    count = is_open_quote(line, '\'');
    flag = 0;
	word = malloc(to_alloc(line) + 1);
	
	if (count == 0)
	{
		
		while (line[i])
		{
			if(line[i] == 39 && flag == 0)
			{
				flag = 1;
				i++;
			}
			if(line[i] != 39)
			{
				word[j] = line[i];
				i++;
				j++;
			}
			if(line[i] == 39 && flag == 1)
			{
				i++;	
				break;
			}
		}
		word[j] = '\0';
		addback(tokens, word, WORD);
	}
	else
	{
		write(1, "Open quote\n", ft_strlen("Open quote\n"));
		ft_lstclear(tokens);
		*open = 1;
	}
	return (line + i);
}

char	*is_dquote(t_token_list **tokens, char *line)
{
	int i;
    int j;
    int flag;
    char    *word;

    i = 0;
    j = 0;
    flag = 0;
	word = malloc(to_alloc(line) + 1);	

		while (line[i])
		{
			if (line[i] == 34 && flag == 0)
			{
				i++;
				flag = 1;
			}
			if(line[i] != 34)
			{
				word[j] = line[i];
				i++;
				j++;	
			}
			if (line[i] == '|')
				break;
				
            if (line[i] == '$')
                break;
			else if (line[i] == 34)
			{
				flag = 0;
				i++;
				break;
			}
			
		}
        if (j > 0)
        {
            word[j]= '\0';
            addback(tokens, word, WORD);
        }
	return (line + i);
}

char	*afdollar(t_token_list **tokens, char *line)
{
	int	i;
	int j;
	char *afdollar;

	i = 0;
	j = 0;
	line = is_dollar_pipe(tokens, line);
	while (line[i])
	{
		if (line[i] != 34)
			i++;
		else
			break;
	}
	afdollar = malloc(i + 1);
	while (j < i)
	{
		afdollar[j] = line[j];
		j++;
	}
	afdollar[j] = '\0';
	addback(tokens, afdollar, AFDOLLAR);
	if (line[i] == 34 && !line[i + 1])
		return (line + i + 1);
	return (line + i);
}