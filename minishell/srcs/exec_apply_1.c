/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:57:32 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 12:57:34 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_tilda(t_list *curr)
{
	char		*temp;
	t_glob_data	*gdata;
	char		*home;

	ft_link(&gdata);
	home = get_var_value("HOME", gdata->data);
	if (!home)
		home = "";
	while (curr)
	{
		if (curr->data[0] == '~' && curr->data[1] == 0)
		{
			free(curr->data);
			curr->data = ft_strdup(home);
		}
		else if (curr->data[0] == '~' && curr->data[1] == '/')
		{
			temp = curr->data;
			curr->data = ft_strjoin(home, curr->data + 1);
			free(temp);
		}
		curr = curr->next;
	}
}

pid_t	apply_pipe(int *curr_fd)
{
	pid_t		pid;
	int			pipe_fd[2];
	t_glob_data	*gdata;

	ft_link(&gdata);
	pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid != 0)
	{
		close(pipe_fd[1]);
		curr_fd[0] = dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		return (pid);
	}
	else
	{
		gdata->main_proc_mark = 0;
		close(pipe_fd[0]);
		curr_fd[1] = dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		return (pid);
	}
}

int	apply_output_token(t_list **rdr_token)
{
	int	fd;

	if ((*rdr_token)->type == OUTPUT || (*rdr_token)->type == APPEND)
	{
		if ((*rdr_token)->type == OUTPUT)
			fd = open((*rdr_token)->data, O_CREAT | O_RDWR | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = open((*rdr_token)->data, O_CREAT | O_RDWR | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			ft_print_error(errno, (*rdr_token)->data);
			return (-1);
		}
		dup2(fd, 1);
		fd_mem(fd, PUSH);
	}
	*rdr_token = (*rdr_token)->next;
	return (0);
}
