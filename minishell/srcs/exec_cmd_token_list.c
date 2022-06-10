/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 20:45:17 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 20:45:20 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_brc(t_complex_return *ret,
	t_exec_info *info, t_cmd_token **curr_cmd_token)
{
	pid_t		pid;
	t_glob_data	*gdata;

	ft_link(&gdata);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		*ret = execute_cmd_list((*curr_cmd_token)->cmd_list);
		ret->terminate = 1;
		gdata->main_proc_mark = 0;
	}
	else
	{
		close(0);
		close(1);
		waitpid(pid, &gdata->last_exit_code, 0);
		g_convert_exit_code();
		ret->terminate = info->finish_br_if_pipe;
	}
}

static int	exec_brc_w_apl(t_cmd_token **curr_cmd_token, t_exec_info *info,
				t_complex_return *ret)
{
	info->finish_br_if_pipe = 0;
	if ((*curr_cmd_token)->next && (*curr_cmd_token)->next->type == PIPE)
	{
		if (apply_pipe(info->curr_fd) != 0)
		{
			*curr_cmd_token = (*curr_cmd_token)->next->next;
			return (CONTINUE);
		}
		else
			info->finish_cmd_if_pipe = 1;
		info->finish_br_if_pipe = 1;
	}
	if (!apply_redirect_token(*curr_cmd_token))
	{
		fork_brc(ret, info, curr_cmd_token);
		if (ret->terminate)
			return (1);
	}
	return (0);
}

static int	exec_cmd_w_apl(t_cmd_token **curr_cmd_token, t_exec_info *info,
				t_complex_return *ret, t_cmd_list *curr_cmd_list)
{
	if ((*curr_cmd_token)->next && (*curr_cmd_token)->next->type == PIPE)
	{
		if (apply_pipe(info->curr_fd) != 0)
		{
			(*curr_cmd_token) = (*curr_cmd_token)->next->next;
			return (CONTINUE);
		}
		else
			info->finish_cmd_if_pipe = 1;
		if (curr_cmd_list->piped)
			info->finish_cmd_if_pipe = 1;
	}
	if (!apply_redirect_token(*curr_cmd_token))
	{
		*ret = execute_cmd((*curr_cmd_token),
				info->finish_cmd_if_pipe, curr_cmd_list);
		if (ret->terminate)
			return (1);
	}
	return (0);
}

int	exec_cmd_token_list(t_exec_info *info,
		t_cmd_list *curr_cmd_list, t_complex_return *ret)
{
	t_cmd_token			*curr_cmd_token;
	int					ret2;

	curr_cmd_token = curr_cmd_list->cmd_token;
	while (curr_cmd_token)
	{
		info->finish_cmd_if_pipe = 0;
		if (curr_cmd_token->type == BRC || curr_cmd_token->type == CMD)
		{
			if (curr_cmd_token->type == BRC)
				ret2 = exec_brc_w_apl(&curr_cmd_token, info, ret);
			else
				ret2 = exec_cmd_w_apl(&curr_cmd_token, info,
						ret, curr_cmd_list);
			if (ret2 == CONTINUE)
				continue ;
			else if (ret2 == 1)
				return (1);
		}
		curr_cmd_token = curr_cmd_token->next;
	}
	return (0);
}
