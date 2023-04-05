/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:06:00 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/05 15:20:20 by samjaabo         ###   ########.fr       */
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
	else if (list->type == COMMAND || list->type == COMMAND_ARG)
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
	int		ids;

	ids = 0;
	head = NULL;
	cmd = ft_lstnew(ids++);
	if (!cmd)
		return (NULL);
	ft_addlast(&head, cmd);
	while (list)
	{
		if (list->type == PIPE)
		{
			cmd = ft_lstnew(ids++);
			if (!cmd)
				return (ftx_lstclear(&head) ,NULL);
			ft_addlast(&head, cmd);
		}
		if (ft_trans_args(list, cmd) == ERROR)
			return (ftx_lstclear(&head), NULL);
		list = list->next;
	}
	return (head);
}