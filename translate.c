/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:06:00 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/04 17:27:29 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	ft_trans_args(t_list *list, t_cmd *cmd)
{
	if (list->type == FILE_TO_STDIN || list->type == HERE_DOCUMENT ||
		list->type == APPEND_TO_FILE || list->type == WRITE_TO_FILE)
	{
		list->next->type = MYFILE;
		cmd->types = ft_realloc(cmd->types, ft_strdup(ft_itoa(list->type)));
		cmd->redirs = ft_realloc(cmd->redirs,
				ft_strdup(list->next->value));
		if (!cmd->types || !cmd->redirs)
			return (ERROR);
	}
	else if (list->type == COMMAND)
	{
		cmd->args = ft_realloc(cmd->args, ft_strdup(list->value));
		if (!cmd->args)
			return (ERROR);
	}
	return (SUCCESS);
}

t_cmd	*ft_translate(t_list *list)
{
	t_cmd	*cmd;
	t_cmd	*head;

	head = NULL;
	cmd = ft_lstnew();
	if (!cmd)
		return (NULL);
	ft_addlast(&head, cmd);
	while (list)
	{
		if (list->type == PIPE)
		{
			cmd = ft_lstnew();
			if (!cmd)
				return (ftx_lstclear(&head) ,NULL);
			ft_addlast(&head, cmd);
		}
		if (ft_trans_args(list, cmd) == ERROR)
			return (ftx_lstclear(&head),exit(12), NULL);
		//printf("%s\n", list->value);
		list = list->next;
	}
	return (head);
}