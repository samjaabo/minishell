/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:40 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/07 16:26:49 by samjaabo         ###   ########.fr       */
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
		// ft_printcmd(head);
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

	line = readline("\e[1;32mminishell\e[0m\e[1;91m$\e[0m ");
	//line = readline("/samjaabo/files$ ");
	add_history(line);
	
	line = remove_additional_spaces(line);
    return (line);
}

int main(int i, char **v, char **env)
{
    char	*line;

	(void)v;
	(void)i;
	system("clear");
	ft_dup_default_stdio();
    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);
		body(line, env);
    }
	close(3);
	close(4);
	close(5);
}
