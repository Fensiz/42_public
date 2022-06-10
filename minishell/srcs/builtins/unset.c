/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:44:57 by bteak             #+#    #+#             */
/*   Updated: 2021/12/14 16:07:10 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_if_first(t_env **begin_list, char *name_to_remove)
{
	t_env	*next;

	if (!*begin_list)
		return ;
	while (*begin_list && ft_strcmp((*begin_list)->var_name,
			name_to_remove) == 0)
	{
		next = (*begin_list)->next;
		free((*begin_list)->var_name);
		free((*begin_list)->value);
		free(*begin_list);
		*begin_list = next;
	}
}

static void	ft_remove_env(t_env **begin_list, char *name_to_remove)
{
	t_env	*current;
	t_env	*next;

	remove_if_first(begin_list, name_to_remove);
	if (!*begin_list)
		return ;
	current = *begin_list;
	while (current && current->next)
	{
		if (ft_strcmp(current->next->var_name, name_to_remove) == 0)
		{
			next = current->next->next;
			free(current->next->value);
			free(current->next->var_name);
			free(current->next);
			current->next = next;
		}
		else
			current = current->next;
	}
}

static void	unset_error(char *name)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	ft_putstr_fd("msh: unset: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	gdata->last_exit_code = 1;
}

static void	remove_env(char *name)
{
	char		*env;
	t_glob_data	*gdata;

	ft_link(&gdata);
	env = NULL;
	env = get_env(name);
	if (env)
		ft_remove_env(&gdata->data->env_parsed, name);
	if (ft_strcmp(name, "PATH") == 0)
	{
		free_path();
		gdata->data->path = NULL;
	}
}

void	unset_cmd(char **argv)
{
	int			i;
	t_glob_data	*gdata;

	ft_link(&gdata);
	gdata->last_exit_code = 0;
	if (!argv[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		gdata->last_exit_code = 2;
	}
	i = 1;
	while (argv[i])
	{
		if (is_valid_env(argv[i]))
			remove_env(argv[i]);
		else
			unset_error(argv[i]);
		i++;
	}
}
