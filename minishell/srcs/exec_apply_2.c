/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_apply_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:22:19 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 22:22:20 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_loop(char *input, t_list *rdr_token, int fd)
{
	signal(SIGINT, sig_void2);
	input = readline("> ");
	signal(SIGINT, sig_void);
	if (input == NULL)
	{
		return (-1);
	}
	if (ft_strcmp(input, rdr_token->data) == 0)
	{
		free(input);
		return (BREAK);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	free(input);
	return (0);
}

static int	heredoc(int *last, char *input, t_list *rdr_token)
{
	int	fd;
	int	ret;

	fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		ft_print_error(errno, rdr_token->data);
		return (-1);
	}
	while (1)
	{
		ret = heredoc_loop(input, rdr_token, fd);
		if (ret == BREAK)
			break ;
		else if (ret == -1)
		{
			close(fd);
			return (-1);
		}
	}
	close(fd);
	*last = HEREDOC;
	return (0);
}

static int	apply_input_token(int *last, char *input, t_list **rdr_token)
{
	int	fd;

	if ((*rdr_token)->type == INPUT)
	{
		fd = open((*rdr_token)->data, O_RDONLY);
		if (fd == -1)
		{
			ft_print_error(errno, (*rdr_token)->data);
			return (-1);
		}
		dup2(fd, 0);
		fd_mem(fd, PUSH);
		*last = INPUT;
	}
	else if ((*rdr_token)->type == HEREDOC)
	{
		if (heredoc(last, input, (*rdr_token)))
			return (-1);
	}
	*rdr_token = (*rdr_token)->next;
	return (0);
}

static int	heredoc_reader(int last)
{
	int	fd;

	if (last == HEREDOC)
	{
		fd = open(".tmp", O_RDONLY);
		if (fd == -1)
		{
			ft_print_error(errno, ".tmp");
			return (-1);
		}
		dup2(fd, 0);
		fd_mem(fd, PUSH);
	}
	return (0);
}

int	apply_redirect_token(t_cmd_token *cmd_token)
{
	t_list	*rdr_token;
	char	*input;
	int		last;

	last = 0;
	input = NULL;
	rdr_token = cmd_token->redirect_list;
	while (rdr_token)
	{
		if (apply_input_token(&last, input, &rdr_token))
			return (-1);
	}
	rdr_token = cmd_token->redirect_list;
	while (rdr_token)
	{
		if (apply_output_token(&rdr_token))
			return (-1);
	}
	if (heredoc_reader(last))
		return (-1);
	return (0);
}
