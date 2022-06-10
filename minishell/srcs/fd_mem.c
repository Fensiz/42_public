/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:54:40 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 12:54:41 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fd_push(t_fd_stack **stack, int fd)
{
	t_fd_stack	*new;
	t_fd_stack	*curr;

	curr = *stack;
	new = (t_fd_stack *)malloc(sizeof(t_fd_stack));
	if (!new)
		exit(1);
	new->fd = fd;
	new->next = NULL;
	if (curr)
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		*stack = new;
}

int	fd_mem(int fd, int action)
{
	static t_fd_stack	*stack;
	t_fd_stack			*curr;
	int					ret;

	ret = 0;
	curr = stack;
	if (action == PUSH)
	{
		fd_push(&stack, fd);
		ret = 1;
	}
	else if (action == CLEAR)
	{
		curr = stack;
		while (curr)
		{
			close(curr->fd);
			stack = curr->next;
			free(curr);
			curr = stack;
		}
		stack = NULL;
		ret = 1;
	}
	return (ret);
}
