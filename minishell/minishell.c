/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:06:40 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/15 21:48:45 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

t_cmd	*body(char *line)
{
	t_token_list	*tokens;
	t_token_list	*finals;
	t_cmd			*head;

	tokens = tokenizer(line);
	syntax_red(&tokens);
	syntax_pipe(&tokens);
	finals = NULL;
	finals_m(tokens, &finals);
	ft_lstclear(&tokens);
	head = ft_translate(finals);
	ft_lstclear(&finals);
	// ft_exec(head, getenv("PATH"), env);
	// while (finals)
	// {
	// 	printf("*%s*  %d\n", finals->value, finals->type);
	// 	finals = finals->next;
	// }
	return (head);
}
// char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
// char	*ft_strrchr(const char *s, int c);
// typedef struct s_data {
// 	char			**env;
// 	int				status;
// 	int				exit_status;
// 	int				new_stdin;
// 	int				new_stdout;
// 	int				new_stderr;
// 	int				pipe_in;
// 	int				pipe_out;
// 	char			*succ_str;
// 	char			*fail_str;
// }	t_data;

// t_data	g_data;
void	ft_control_d(void);
char	*ft_readline_nottty(void);
char	*prompt(int exit_status, char *succ, char *fail)
{
    static char	*line = NULL;
	char		*s;

	// if (111111111111111)
	// 	line = ft_readline_nottty();
	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDOUT_FILENO))
		{
			if (exit_status == 0)
				line = readline(succ);
			else
				line = readline(fail);
		}
		else
			line = readline("");
	}
	else
		line = ft_readline_nottty();
	if (!line)
		ft_control_d();
	if (line && line[0] && isatty(STDIN_FILENO))
		add_history(line);
	s = remove_additional_spaces(line);
    return (s);
}
