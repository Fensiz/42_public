/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:47:57 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 15:42:34 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_home(void)
{
	char		*home;
	t_glob_data	*gdata;

	ft_link(&gdata);
	home = NULL;
	home = get_env("HOME");
	if (!home)
	{
		ft_putstr_fd("msh: echo: HOME not set", 2);
		gdata->last_exit_code = 1;
	}
	else
		ft_putstr_fd(home, 1);
}

static void	echo_args(char **argv, int i)
{
	int		size;

	size = 0;
	while (argv[size])
		size++;
	size -= i;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "~") == 0)
			echo_home();
		else
			ft_putstr_fd(argv[i], 1);
		if (size > 1)
		{
			ft_putchar(' ');
			size--;
		}
		i++;
	}
}

void	echo_cmd(char **argv)
{
	int			n_arg;
	int			i;
	t_glob_data	*gdata;

	ft_link(&gdata);
	gdata->last_exit_code = 0;
	n_arg = 0;
	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		n_arg = 1;
		i++;
	}
	echo_args (argv, i);
	if (!n_arg)
		ft_putchar('\n');
}
