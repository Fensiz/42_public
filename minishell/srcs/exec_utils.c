/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:59:07 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 12:59:09 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	g_convert_exit_code(void)
{
	int			kill_code;
	int			exit_code;
	t_glob_data	*gdata;

	ft_link(&gdata);
	kill_code = gdata->last_exit_code << 8 >> 8;
	exit_code = gdata->last_exit_code >> 8;
	if (exit_code > 256)
		exit_code = 255;
	if (!exit_code && kill_code && kill_code != 13)
	{
		write(1, "\n", 1);
		gdata->last_exit_code = kill_code + 128;
	}
	else
		gdata->last_exit_code = exit_code;
}

char	**list_to_argv(t_list *arg)
{
	char	**argv;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize(arg);
	argv = (char **)malloc((size + 1) * sizeof(char *));
	if (!argv)
		exit(1);
	argv[size] = NULL;
	while (arg)
	{
		argv[i] = ft_strdup(arg->data);
		arg = arg->next;
		i++;
	}
	return (argv);
}
