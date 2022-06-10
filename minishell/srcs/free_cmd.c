/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:11:34 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 11:11:37 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_list **token)
{
	t_list	*curr;
	t_list	*next;

	curr = *token;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
}

void	free_cmd_content(t_cmd_token *data)
{
	t_list_cmplx	argv;
	t_list_cmplx	redir;

	argv.curr = data->argv;
	while (argv.curr)
	{
		argv.next = argv.curr->next;
		free(argv.curr->data);
		free(argv.curr);
		argv.curr = argv.next;
	}
	redir.curr = data->redirect_list;
	while (redir.curr)
	{
		redir.next = redir.curr->next;
		free(redir.curr->data);
		free(redir.curr);
		redir.curr = redir.next;
	}
}

void	free_cmd_token_list(t_cmd_token **data)
{
	t_cmd_token_cmplx	cmd_token;

	cmd_token.curr = *data;
	while (cmd_token.curr)
	{
		cmd_token.next = cmd_token.curr->next;
		if (cmd_token.curr->type == BRC)
		{
			free_cmd_list(&cmd_token.curr->cmd_list);
			free_cmd_content(cmd_token.curr);
		}
		else if (cmd_token.curr->type == CMD)
			free_cmd_content(cmd_token.curr);
		free(cmd_token.curr);
		cmd_token.curr = cmd_token.next;
	}
}

void	free_cmd_list(t_cmd_list **data)
{
	t_cmd_list_cmplx	cmd_list;

	cmd_list.curr = *data;
	while (cmd_list.curr)
	{
		cmd_list.next = cmd_list.curr->next;
		free_cmd_token_list(&cmd_list.curr->cmd_token);
		free(cmd_list.curr);
		cmd_list.curr = cmd_list.next;
	}
}

void	free_argv(char **argv)
{
	char	**curr;

	curr = argv;
	while (*curr)
	{
		free(*curr);
		curr++;
	}
	free(argv);
}
