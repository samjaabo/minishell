/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoussef <byoussef@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:05:43 by byoussef          #+#    #+#             */
/*   Updated: 2023/03/31 16:05:44 by byoussef         ###   ########.fr       */
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
	t_token_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		tmp = tmp->next;
		free(*lst);
		*lst = tmp;
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