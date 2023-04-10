/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:05:43 by byoussef          #+#    #+#             */
/*   Updated: 2023/04/07 22:54:32 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_lstadd_back(t_token_list **lst, t_token_list *new)
{
	t_token_list	*tmp;

	tmp = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

t_token_list	*ft_lstlast(t_token_list *head)
{
	t_token_list	*ptr;

	ptr = head;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_lstclear(t_token_list	**lst)
{
	t_token_list	*next;
	t_token_list	*head;

	head = *lst;
	while (head)
	{
		next = head->next;
		free(head->value);
		free(head);
		head = next;
	}
	*lst = NULL;
}

t_token_list	*ft_lstnew(int content, int type)
{
	t_token_list	*new;

	new = malloc(sizeof(t_token_list));
	if (!new)
		return (NULL);
	new->type = type;
    new->value = content;
	new -> next = NULL;
	return (new);
}

int	ft_lstsize(t_token_list	*lst)
{
	int		count;
	t_token_list	*ptr;

	count = 0;
	if (lst == NULL)
		return (0);
	ptr = lst;
	while (ptr)
	{
		count++;
		ptr = ptr ->next;
	}
	return (count);
}