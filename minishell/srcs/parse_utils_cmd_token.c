/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:55:40 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 12:55:42 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_token	*cmd_token_create(void)
{
	t_cmd_token	*new;

	new = (t_cmd_token *)malloc(sizeof(t_cmd_token));
	if (!new)
		exit(1);
	new->type = 0;
	new->argv = NULL;
	new->cmd_list = NULL;
	new->redirect_list = NULL;
	new->next = NULL;
	return (new);
}

t_cmd_token	*addback_new_cmdtoken(t_cmd_token **cmd_token, int type)
{
	t_cmd_token	*curr;

	curr = *cmd_token;
	if (curr == NULL)
	{
		*cmd_token = cmd_token_create();
		(*cmd_token)->type = type;
		curr = *cmd_token;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = cmd_token_create();
		curr = curr->next;
		curr->type = type;
	}
	return (curr);
}
