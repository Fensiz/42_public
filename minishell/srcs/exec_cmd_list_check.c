/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:37:50 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 22:37:53 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ccl_help(t_cmd_token **tok)
{
	if ((*tok)->type == BRC && (*tok)->next && (*tok)->next->type == BRC)
		return (1);
	else if ((*tok)->type == BRC && (*tok)->next && (*tok)->next->type == CMD)
		return (1);
	else if ((*tok)->type == CMD && (*tok)->next && (*tok)->next->type == BRC)
		return (1);
	else if ((*tok)->type == BRC)
	{
		if (check_cmd_list((*tok)->cmd_list))
			return (1);
	}
	else if ((*tok)->type == PIPE && (*tok)->next && (*tok)->next->type == PIPE)
		return (1);
	*tok = (*tok)->next;
	return (0);
}

int	check_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list	*cmd;
	t_cmd_token	*tok;

	cmd = cmd_list;
	while (cmd)
	{
		tok = cmd->cmd_token;
		if (tok->type == PIPE)
			return (1);
		while (tok)
		{
			if (ccl_help(&tok))
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
