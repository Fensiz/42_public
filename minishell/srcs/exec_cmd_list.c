/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 21:03:24 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 21:03:26 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fork_piped(t_cmd_list **curr_cmd_list, t_complex_return *ret)
{
	pid_t		pid;
	t_glob_data	*gdata;

	ft_link(&gdata);
	if ((*curr_cmd_list)->piped)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		ret->terminate = 0;
		if (pid)
		{
			waitpid(pid, &gdata->last_exit_code, 0);
			g_convert_exit_code();
			ret->exit_code = gdata->last_exit_code;
			*curr_cmd_list = (*curr_cmd_list)->next;
			return (CONTINUE);
		}
		else
		{
			gdata->main_proc_mark = 0;
			ret->exit_code = 0;
		}
	}
	return (0);
}

static void	ecl_init(t_complex_return *ret, t_exec_info *info)
{
	ret->exit_code = 0;
	ret->terminate = 0;
	info->def_fd[0] = dup(0);
	info->def_fd[1] = dup(1);
	fd_mem(info->def_fd[0], PUSH);
	fd_mem(info->def_fd[1], PUSH);
}

static int	braker_duper(int i, t_cmd_list **curr_cmd_list, t_exec_info *info)
{
	if (i == 0 && (*curr_cmd_list)->piped)
		return (BREAK);
	*curr_cmd_list = (*curr_cmd_list)->next;
	dup2(info->def_fd[0], 0);
	dup2(info->def_fd[1], 1);
	return (0);
}

t_complex_return	execute_cmd_list(t_cmd_list *curr_cmd_list)
{
	t_exec_info			info;
	t_complex_return	ret;
	int					i;
	t_glob_data			*gdata;

	ft_link(&gdata);
	ecl_init(&ret, &info);
	while (curr_cmd_list)
	{
		i = 1;
		if ((curr_cmd_list->logic_mark == L_OR && gdata->last_exit_code != 0)
			|| (curr_cmd_list->logic_mark == L_AND
				&& gdata->last_exit_code == 0)
			|| curr_cmd_list->logic_mark == 0)
		{
			i = fork_piped(&curr_cmd_list, &ret);
			if (i == CONTINUE)
				continue ;
			if (exec_cmd_token_list(&info, curr_cmd_list, &ret))
				return (ret);
		}
		if (braker_duper(i, &curr_cmd_list, &info) == BREAK)
			break ;
	}
	return (ret);
}
