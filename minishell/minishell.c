/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:40 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/04 17:22:42 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
void	ft_printcmd(t_cmd *head);

void	body(char *line, char **env)
{
	t_token_list	*tokens;
	t_token_list	*finals;
	t_cmd	*head;

		tokens = tokenizer(line);
		syntax_red(&tokens);
		syntax_pipe(&tokens);
		char *c;
		finals = NULL;
		c = NULL;
		finals_m(tokens, &finals);
		head = ft_translate(finals);
		//ft_printcmd(head);
		ft_exec(head, getenv("PATH"), env);
		// while (finals)
		// {
		// 	printf("*%s*  %d\n", finals->value, finals->type);
		// 	finals = finals->next;
		// }
}

char    *prompt(void)
{
    char	*line;

	line = readline("[minishell]$ ");
	add_history(line);
	
	line = remove_additional_spaces(line);
    return (line);
}

int main(int i, char **v, char **env)
{
    char	*line;

	(void)v;
	(void)i;
    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);
		body(line, env);
    }
}
