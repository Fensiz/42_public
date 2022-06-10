/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_star.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:58:29 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 12:58:32 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	with_star(char *str)
{
	while (*str)
	{
		if (*str == -120)
			return (1);
		str++;
	}
	return (0);
}

static void	dup_elem(char *name, t_list **token_list)
{
	t_list			*new_token;

	new_token = token_create();
	new_token->data = ft_strdup(name);
	ft_lstadd_back(token_list, new_token);
}

static void	star_fill(char *str)
{
	while (*str)
	{
		if (*str == -120)
			*str = '*';
		str++;
	}
}

void	split_arg_to_args(t_list *arg, t_list **arg_new)
{
	t_list	*new_arg_list;

	new_arg_list = NULL;
	while (arg)
	{
		if (with_star(arg->data))
		{
			if (!find_file(arg->data, &new_arg_list))
			{
				star_fill(arg->data);
				dup_elem(arg->data, &new_arg_list);
			}
		}
		else
			dup_elem(arg->data, &new_arg_list);
		arg = arg->next;
	}
	free_tokens(arg_new);
	*arg_new = new_arg_list;
}

void	ft_list_dup(t_list *lst, t_list **n_lst)
{
	t_list	*new;
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		new = token_create();
		ft_parser(lst, &new->data);
		new->type = lst->type;
		ft_lstadd_back(&new_lst, new);
		lst = lst->next;
	}
	*n_lst = new_lst;
}
