/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:56:10 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 15:42:50 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_clear(t_env **lst)
{
	t_env	*temp;
	t_env	*env;

	if (!lst)
		return ;
	env = *lst;
	while (env)
	{
		free(env->var_name);
		free(env->value);
		temp = env->next;
		free(env);
		env = temp;
	}
	*lst = NULL;
	free(lst);
}

int	is_valid_env(char *str)
{
	int		i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (i == 0 && (ft_isdigit(str[i])))
			return (0);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_env(char *argv)
{
	char		*value;
	t_env		*tmp;
	t_glob_data	*gdata;

	ft_link(&gdata);
	value = NULL;
	tmp = gdata->data->env_parsed;
	while (tmp)
	{
		if (ft_strcmp(argv, tmp->var_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (value);
}

int	set_env(char *env, char *value)
{
	t_env		*curr;
	char		*temp;
	t_glob_data	*gdata;

	ft_link(&gdata);
	curr = gdata->data->env_parsed;
	while (curr)
	{
		if (ft_strcmp(env, curr->var_name) == 0)
		{
			temp = curr->value;
			curr->value = ft_strdup(value);
			free(temp);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void	env_cmd(void)
{
	int			i;
	t_env		*tmp;
	t_data		*data;
	t_glob_data	*gdata;

	ft_link(&gdata);
	i = 0;
	data = gdata->data;
	tmp = data->env_parsed;
	while (tmp)
	{
		if (tmp->value && tmp->var_name)
		{
			ft_putstr_fd(tmp->var_name, 1);
			ft_putchar('=');
			ft_putstr_fd(tmp->value, 1);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
	gdata->last_exit_code = 0;
}
