/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:49:44 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 15:54:30 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_cmd(void)
{
	char		*cwd;
	t_glob_data	*gdata;

	ft_link(&gdata);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		log_error("pwd");
		return (errno);
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar('\n');
	free(cwd);
	gdata->last_exit_code = 0;
	return (0);
}
