/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:56:11 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 14:59:13 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*ft_listnew(char *value, int type)
{
	t_list		*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (node);
	ft_bzero(node, sizeof(t_list));
	node->type = type;
	node->value = value;
	return (node);
}

void	ft_listaddlast(t_list **head, t_list *new)
{
	t_list	*node;

	node = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (node->next)
		node = node->next;
	node->next = new;
}

// void	ft_listclear(t_list **head)
// {
// 	t_list	*node;
// 	t_list	*next;

// 	node = *head;
// 	while (node)
// 	{
// 		next = node->next;
// 		free(node->value);
// 		node = next;
// 	}
// 	*head = NULL;
// }

// int	main(int argc, char **argv, char **env)
// {
// 	t_cmd	*head;
// 	t_list	*list;
// 	//char	s[]="/bin/echo";
// 	char  **ar;
// 	char  **cp;
// 	char *s;
// 	int i;
// 	// int fds[2];
// 	int fd;

// 	ft_listaddlast(&list, ft_listnew(argv[1],COMMAND));
// 	i = 2;
// 	while (argv[i])
// 	{
// 		printf("-->%s\n", argv[i]);
// 		if (ft_strncmp(argv[i], "<", ft_strlen(argv[i])) == 0)
// 		{
// 			ft_listaddlast(&list, ft_listnew("<", FILE_TO_STDIN));
// 			ft_listaddlast(&list, ft_listnew(argv[++i], -42));
// 		}
// 		else if (ft_strncmp(argv[i], "<<", ft_strlen(argv[i])) == 0)
// 		{
// 			ft_listaddlast(&list, ft_listnew("<<", HERE_DOCUMENT));
// 			ft_listaddlast(&list, ft_listnew(argv[++i], -42));
// 		}
// 		else if (ft_strncmp(argv[i], ">", ft_strlen(argv[i])) == 0)
// 		{
// 			ft_listaddlast(&list, ft_listnew(">", WRITE_TO_FILE));
// 			ft_listaddlast(&list, ft_listnew(argv[++i], -42));
// 		}
// 		else if (ft_strncmp(argv[i], ">>", ft_strlen(argv[i])) == 0)
// 		{
// 			ft_listaddlast(&list, ft_listnew(">>", APPEND_TO_FILE));
// 			ft_listaddlast(&list, ft_listnew(argv[++i], -42));
// 		}
// 		else if (ft_strncmp(argv[i], "|", ft_strlen(argv[i])) == 0)
// 		{
// 			ft_listaddlast(&list, ft_listnew("|", PIPE));
// 			ft_listaddlast(&list, ft_listnew(argv[++i], COMMAND));
// 		}
// 		else
// 		{
// 			ft_listaddlast(&list, ft_listnew(argv[i], COMMAND_ARG));
// 		}
// 		++i;
// 	}

// 	// ft_listaddlast(&list, ft_listnew("echo", COMMAND));
// 	// ft_listaddlast(&list, ft_listnew("hello world!", COMMAND_ARG));
// 	// ft_listaddlast(&list, ft_listnew("<<", HERE_DOCUMENT));
// 	// ft_listaddlast(&list, ft_listnew("SAID", INT32_MAX));
// 	// ft_listaddlast(&list, ft_listnew(">", WRITE_TO_FILE));
// 	// ft_listaddlast(&list, ft_listnew("file.me", INT32_MAX));


// 	head = ft_translate(list);
// 	if (!head)
// 		return (12);
// 	//ft_printcmd(head);
// 	ft_exec(head, getenv("PATH"), env);
// 	// ft_dup_default_stdio();
// 	// ar = malloc(sizeof(char *) * 3);
// 	// ar[0] = ft_strdup("./tmp/file");
// 	// ar[1] = "HEllo world\n";
// 	// ar[2] = NULL;
// 	// head = NULL;
// 	// ft_addlast(&head, ft_lstnew(ft_strdup("/bin/cat"), (char [1]){"", NULL}, HERE_DOCUMENT, "ok"));
// 	// ft_addlast(&head, ft_lstnew(ft_strdup("/bin/echo"), ar, READ_FROM_FILE, "./tmp/file"));
// 	// ft_addlast(&head, ft_lstnew(ft_strdup("/bin/echo"), ar, WRITE_TO_FILE,  "./tmp/file"));
// 	// ft_addlast(&head, ft_lstnew(s, ar, APPEND_TO_FILE,  "./tmp/file"));
// 	//ft_exec(head, env);
// 	//ft_lstclear(&head);
// 	// printf("%s\n", argv[1]);
// 	// s = ft_get_cmd_path(getenv("PATH"), argv[1]);
// 	// if(!s)
// 	// 	return 0;
// 	//printf("%s\n", s);
// 	// ar = (char *)((const char *[3]){s, argv[2], NULL});
// 	//printf("%s - %s\n", ar[0], ar[2]);
// 	// execve(s, ar, env);
// 	// printf("ssss\n");
// 	// // execve(s, &argv[1], env)
// 	// errno = ENOMEM;
// 	// // printf("%s\n", strerror(ENOMEM));
// 	// fd = 0;
// 	// while (fd < 55)
// 	// 	ft_perror("malloc", ++fd);
// 	//free(s);
// 	//system("leaks program");
// 	ft_lstclear(&head);
// 	return (0);
// }
