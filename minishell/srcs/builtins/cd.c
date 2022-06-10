/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:38:56 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 17:53:21 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_pwd(void)
{
	char		*curr_dir;
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (get_env("PWD") && get_env("OLDPWD"))
		set_env("OLDPWD", get_env("PWD"));
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory\n", 2);
		gdata->last_exit_code = errno;
		return (errno);
	}
	if (get_env("PWD"))
		set_env("PWD", curr_dir);
	free(curr_dir);
	return (0);
}

static void	cd_hlp(char *args)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	ft_putstr_fd("msh: cd: ", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (errno)
		gdata->last_exit_code = 1;
	else
		gdata->last_exit_code = 0;
}

static int	oldpwd_error(void)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (errno)
	{
		ft_putstr_fd("msh: cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd("msh: cd: OLDPWD not set\n", 2);
	gdata->last_exit_code = 1;
	return (1);
}

static int	cd_with_args(char **args)
{
	t_glob_data	*gdata;
	char		*oldpwd;

	ft_link(&gdata);
	errno = 0;
	oldpwd = NULL;
	if (ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = get_env("OLDPWD");
		if (!oldpwd || chdir(oldpwd))
			return (oldpwd_error());
		else
			pwd_cmd();
	}
	else
	{
		if (chdir(args[1]))
		{
			cd_hlp(args[1]);
			return (gdata->last_exit_code);
		}
	}
	return (0);
}

int	cd_cmd(char **args)
{
	int			ret;
	t_glob_data	*gdata;
	char		*home;

	ft_link(&gdata);
	home = NULL;
	if (!args[1])
	{
		home = get_env("HOME");
		if (!home || chdir(home))
		{
			ft_putstr_fd("msh: cd: HOME not set\n", 2);
			gdata->last_exit_code = errno;
			return (errno);
		}
	}
	else
	{
		if (cd_with_args(args))
			return (errno);
	}
	ret = change_pwd();
	gdata->last_exit_code = 0;
	return (ret);
}
