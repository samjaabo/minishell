/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:26:06 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/18 15:03:36 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_cmd	*ft_lstnew(int ids)
{
	t_cmd		*node;

	node = ft_calloc(1, sizeof(t_cmd));
	if (!node)
		return (node);
	node->id = ids;
	node->here_doc = -1;
	node->pipe_in = -1;
	node->pipe_out = -1;
	return (node);
}

void	ft_addlast(t_cmd **head, t_cmd *new)
{
	t_cmd	*node;

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

char	*ft_clear(char **ar)
{
	char	**cp;

	if (!ar)
		return (NULL);
	cp = ar;
	while (*ar)
		free(*ar++);
	free(cp);
	return (NULL);
}

void	ftx_lstclear(t_cmd **head)
{
	t_cmd	*node;
	t_cmd	*next;

	node = *head;
	while (node)
	{
		next = node->next;
		ft_clear(node->args);
		ft_clear(node->redirs);
		ft_clear(node->types);
		close(node->here_doc);
		free(node);
		node = next;
	}
	*head = NULL;
}

// void	ft_printcmd(t_cmd *head)
// {
// 	int i;

// 	while (head)
// 	{
// 		i = 0;
// 		printf("========================\ncommand: ");
// 		while (head->args && head->args[i])
// 			printf("%s | ", head->args[i++]);
// 		i = 0;
// 		printf("========================\nredirections: ");
// 		while (head->redirs && head->redirs[i])
// 			printf("(%s %d)| ", head->redirs[i], ft_atoi(head->types[i])),++i;
// 		printf("\n");
// 		head = head->next;
// 	}
// }
void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*ptr;

	if (!lst || !new)
		return ;
	ptr = *lst;
	if (*lst)
	{
		ptr = ft_lstlast(ptr);
		ptr->next = new;
	}
	else
		*lst = new;
}

// void	ft_lstclear(t_cmd **lst)
// {
// 	t_cmd	*ptr;

// 	if (!lst)
// 		return ;
// 	ptr = *lst;
// 	while (ptr)
// 	{
// 		ptr = ptr->next;
// 		free((*lst)->cmd);
// 		ft_free((*lst)->args);
// 		clear_files(&(*lst)->in_file);
// 		clear_files(&(*lst)->out_file);
// 		free(*lst);
// 		*lst = ptr;
// 	}
// 	lst = NULL;
// }

t_cmd	*ft_lstlast(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// t_cmd	*ft_lstnew(void)
// {
// 	t_cmd	*head;

// 	head = malloc(sizeof(t_cmd));
// 	if (!head)
// 		return (NULL);
// 	head->args = NULL;
// 	head->redirs = NULL;
// 	head->types = NULL;
// 	head->next = NULL;
// 	return (head);
// }
