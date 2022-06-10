/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:11:42 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 11:11:43 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	t_env		*curr;
	t_env		*next;
	t_glob_data	*gdata;

	ft_link(&gdata);
	curr = gdata->data->env_parsed;
	while (curr)
	{
		next = curr->next;
		free(curr->value);
		free(curr->var_name);
		free(curr);
		curr = next;
	}
}

void	free_path(void)
{
	char		**curr;
	t_glob_data	*gdata;

	ft_link(&gdata);
	curr = gdata->data->path;
	if (curr)
	{
		while (*curr)
			free(*curr++);
		free(gdata->data->path);
		gdata->data->path = NULL;
	}
}
