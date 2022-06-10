/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:46:07 by bteak             #+#    #+#             */
/*   Updated: 2021/12/10 15:02:31 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	log_error(char *name)
{
	char		*error;
	t_glob_data	*gdata;

	ft_link(&gdata);
	error = strerror(errno);
	ft_putstr_fd("msh: pwd: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	gdata->last_exit_code = errno;
}

void	ft_sort_list(t_env **begin_list, int (*cmp)())
{
	t_env	*ptr;
	t_env	*ptr2;
	char	*name;
	char	*value;

	ptr = *begin_list;
	while (ptr)
	{
		ptr2 = *begin_list;
		while (ptr2->next)
		{
			if ((*cmp)(ptr2->var_name, ptr2->next->var_name) > 0)
			{
				name = ptr2->var_name;
				value = ptr2->value;
				ptr2->var_name = ptr2->next->var_name;
				ptr2->value = ptr2->next->value;
				ptr2->next->var_name = name;
				ptr2->next->value = value;
			}
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
}

static t_complex_return	continue_buildin(char **name, t_complex_return *ret)
{
	if (ft_strcmp(name[0], "env") == 0)
	{
		env_cmd();
		ret->exit_code = 0;
		return (*ret);
	}
	else if (ft_strcmp(name[0], "pwd") == 0)
	{
		ret->exit_code = pwd_cmd();
		return (*ret);
	}
	else if (ft_strcmp(name[0], "export") == 0)
	{
		export_cmd(name);
		ret->exit_code = 0;
		return (*ret);
	}
	else if (ft_strcmp(name[0], "unset") == 0)
	{
		unset_cmd(name);
		ret->exit_code = 0;
		return (*ret);
	}
	return (*ret);
}

t_complex_return	try_buildin(char **name)
{
	t_complex_return	ret;

	ret.terminate = 0;
	ret.exit_code = -1;
	if (ft_strcmp(name[0], "echo") == 0)
	{
		echo_cmd(name);
		ret.exit_code = 0;
		return (ret);
	}
	else if (ft_strcmp(name[0], "cd") == 0)
	{
		ret.exit_code = cd_cmd(name);
		return (ret);
	}
	else if (ft_strcmp(name[0], "exit") == 0)
	{
		ret.terminate = 1;
		ret.exit_code = exit_cmd(name);
		return (ret);
	}
	return (continue_buildin(name, &ret));
}

int	is_buildin(char *cmd_token)
{
	if (ft_strcmp(cmd_token, "echo") == 0
		|| ft_strcmp(cmd_token, "cd") == 0
		|| ft_strcmp(cmd_token, "exit") == 0
		|| ft_strcmp(cmd_token, "env") == 0
		|| ft_strcmp(cmd_token, "pwd") == 0
		|| ft_strcmp(cmd_token, "export") == 0
		|| ft_strcmp(cmd_token, "unset") == 0)
		return (1);
	return (0);
}
