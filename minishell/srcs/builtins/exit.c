/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:57:36 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 18:06:45 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_exit_value(char **argv, int i, t_atoi *arg, t_glob_data *gdata)
{
	if (argv[1])
	{
		*arg = ft_atoi(argv[i - 1], *arg);
		if (arg->value < 0)
			arg->value = 255;
	}
	else
		arg->value = gdata->last_exit_code;
}

int	exit_cmd(char **argv)
{
	int			i;
	t_atoi		arg;
	t_glob_data	*gdata;

	ft_link(&gdata);
	i = 0;
	arg.value = 0;
	arg.error = 0;
	while (argv[i])
		i++;
	if (i > 2)
		ft_putstr_fd("msh: exit: too many arguments", 2);
	get_exit_value(argv, i, &arg, gdata);
	if (arg.error)
	{
		ft_putstr_fd("msh: exit: numeric argument required", 2);
		arg.value = 255;
	}
	return (arg.value);
}
