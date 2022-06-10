/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:53:57 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 12:53:59 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	b_open_handle(t_list **curr,
	t_cmd_token **curr_cmd_token, t_cmd_list **curr_cmd)
{
	int	brc;

	*curr = (*curr)->next;
	*curr_cmd_token = addback_new_cmdtoken(&(*curr_cmd)->cmd_token, BRC);
	if (*curr_cmd_token == NULL)
		return (1);
	if (split_cmd(*curr, &(*curr_cmd_token)->cmd_list))
		return (1);
	brc = 0;
	while ((*curr) && !((*curr)->type == B_CLOSE && brc == 0))
	{
		if ((*curr)->type == B_OPEN)
			brc++;
		else if ((*curr)->type == B_CLOSE)
			brc--;
		(*curr) = (*curr)->next;
	}
	return (0);
}

static void	redir_handle(t_list **curr,
	t_cmd_token **curr_cmd_token, t_cmd_list **curr_cmd)
{
	if ((*curr_cmd)->cmd_token == NULL)
		*curr_cmd_token = addback_new_cmdtoken(&(*curr_cmd)->cmd_token, CMD);
	addback_newtoken(&(*curr_cmd_token)->redirect_list, *curr, REDIRECT);
	*curr = (*curr)->next;
}

static void	text_handle(t_list **curr, t_cmd_token **curr_cmd_token,
						t_cmd_list **curr_cmd)
{
	if ((*curr_cmd)->cmd_token == NULL || (*curr_cmd_token)->type == BRC
		|| (*curr_cmd_token)->type == PIPE)
		*curr_cmd_token = addback_new_cmdtoken(&(*curr_cmd)->cmd_token,
				CMD);
	addback_newtoken(&(*curr_cmd_token)->argv, *curr, ARGV);
}

static int	token_handle(t_list **curr, t_cmd_token **curr_cmd_token,
				t_cmd_list **cmd_list, t_cmd_list **curr_cmd)
{
	if ((*curr)->type == B_OPEN)
	{
		if (b_open_handle(curr, curr_cmd_token, curr_cmd))
			return (1);
	}
	else if ((*curr)->type == L_OR || (*curr)->type == L_AND)
		*curr_cmd = addback_new_cmdlist(cmd_list, (*curr)->type);
	else if ((*curr)->type == PIPE)
	{
		(*curr_cmd)->piped = 1;
		*curr_cmd_token = addback_new_cmdtoken(&(*curr_cmd)->cmd_token, PIPE);
	}
	else if ((*curr)->type == TEXT)
		text_handle(curr, curr_cmd_token, curr_cmd);
	else if ((*curr)->type == OUTPUT || (*curr)->type == APPEND
		|| (*curr)->type == INPUT || (*curr)->type == HEREDOC)
		redir_handle(curr, curr_cmd_token, curr_cmd);
	else if ((*curr)->type == B_CLOSE)
		return (2);
	return (0);
}

int	split_cmd(t_list *curr, t_cmd_list **cmd_list)
{
	t_cmd_list	*curr_cmd;
	t_cmd_token	*curr_cmd_token;
	int			ret;

	*cmd_list = cmd_list_create();
	curr_cmd = *cmd_list;
	curr_cmd_token = curr_cmd->cmd_token;
	ret = 0;
	while (curr)
	{
		ret = token_handle(&curr, &curr_cmd_token, cmd_list, &curr_cmd);
		if (ret == 2)
			break ;
		else if (ret == 1)
			return (1);
		if (curr)
			curr = curr->next;
	}
	return (0);
}
