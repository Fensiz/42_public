/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:16:36 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/14 16:16:38 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_link(t_glob_data **export)
{
	static t_glob_data	data;

	*export = &data;
}

void	sig_void2(int signum)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (signum == SIGINT)
	{
		gdata->last_exit_code = 130;
		close(0);
	}
}

void	fd_close(t_cmd_list *cmd)
{
	if (cmd->piped)
	{
		close(0);
		fd_mem(0, CLEAR);
	}
}
