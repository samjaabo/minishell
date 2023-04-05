/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:26:06 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/05 15:18:34 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_cmd	*ft_lstnew(int ids)
{
	t_cmd		*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (node);
	ft_bzero(node, sizeof(t_cmd));
	node->id = ids;
	node->std_in = STDIN_FILENO;
	node->std_out = STDOUT_FILENO;
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
		node = next;
	}
	*head = NULL;
}

void	ft_printcmd(t_cmd *head)
{
	int i;

	while (head)
	{
		i = 0;
		printf("========================\ncommand: ");
		while (head->args && head->args[i])
			printf("%s | ", head->args[i++]);
		i = 0;
		printf("========================\nredirections: ");
		while (head->redirs && head->redirs[i])
			printf("(%s %d)| ", head->redirs[i], ft_atoi(head->types[i])),++i;
		printf("\n");
		head = head->next;
	}
}
