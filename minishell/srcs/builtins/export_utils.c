/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:47:06 by bteak             #+#    #+#             */
/*   Updated: 2021/12/15 16:27:14 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(t_env *sorted)
{
	t_env	*tmp;

	tmp = sorted;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, "_"))
		{
			if (tmp->value)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->var_name, 1);
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"\n", 1);
			}
			else if (!tmp->value)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->var_name, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		tmp = tmp->next;
	}
}

static void	fill_sorted(t_env **sorted, t_env *tmp)
{
	t_env		*to_add;

	while (tmp)
	{
		to_add = NULL;
		to_add = ft_env_addnew((int)ft_strlen(tmp->var_name),
				(int)ft_strlen(tmp->value));
		ft_strlcpy(to_add->value, tmp->value, ft_strlen(tmp->value) + 1);
		ft_strlcpy(to_add->var_name, tmp->var_name,
			ft_strlen(tmp->var_name) + 1);
		ft_env_addback(sorted, to_add);
		tmp = tmp->next;
	}
}

void	export_no_args(void)
{
	t_env		*tmp;
	t_env		**sorted;
	t_glob_data	*gdata;

	ft_link(&gdata);
	tmp = gdata->data->env_parsed;
	sorted = NULL;
	if (ft_env_size(gdata->data->env_parsed) == 0)
		return ;
	sorted = malloc(sizeof(t_env *) * ft_env_size(gdata->data->env_parsed));
	if (!sorted)
		exit(1);
	*sorted = NULL;
	fill_sorted(sorted, tmp);
	ft_sort_list(sorted, ft_strcmp);
	print_sorted_env(*sorted);
	ft_env_clear(sorted);
}

static int	modify_existing(char **params)
{
	t_env		*tmp;
	char		*to_free;
	t_glob_data	*gdata;

	ft_link(&gdata);
	tmp = gdata->data->env_parsed;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, params[0]) == 0)
		{
			to_free = tmp->value;
			tmp->value = ft_strdup(params[1]);
			free (to_free);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	add_new_env(char **params)
{
	t_env		*new_param;
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (!modify_existing(params))
	{
		new_param = ft_env_addnew((int)ft_strlen(params[0]),
				(int)ft_strlen(params[1]));
		if (!new_param)
			return ;
		ft_strlcpy(new_param->var_name, params[0], ft_strlen(params[0]) + 1);
		ft_strlcpy(new_param->value, params[1], ft_strlen(params[1]) + 1);
		ft_env_addback(&gdata->data->env_parsed, new_param);
	}
}
