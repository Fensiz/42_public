/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:32:41 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 13:32:43 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list	*cmd_list_create(void)
{
	t_cmd_list	*new;

	new = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!new)
		exit(1);
	new->cmd_token = NULL;
	new->piped = 0;
	new->logic_mark = 0;
	new->next = NULL;
	return (new);
}

t_cmd_list	*addback_new_cmdlist(t_cmd_list **cmd_list, int logic_mark)
{
	t_cmd_list	*curr;

	curr = *cmd_list;
	if (curr == NULL)
	{
		*cmd_list = cmd_list_create();
		curr = *cmd_list;
		curr->logic_mark = logic_mark;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = cmd_list_create();
		curr = curr->next;
		curr->logic_mark = logic_mark;
	}
	return (curr);
}
