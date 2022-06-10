/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:44:01 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 20:44:04 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_char(t_temp *t, char *input, t_list **token)
{
	if (t->in_word == 0)
	{
		ft_create_next(token, &t->begin);
		(*token)->type = TEXT;
	}
	ft_charjoin(&(*token)->data, input[t->i]);
	t->in_word++;
}

static int	in_quot(t_temp *t, char *input, t_list **token)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (input[t->i] == '\'')
	{
		t->state = GENERAL;
		ft_charjoin(&(*token)->data, input[t->i]);
	}
	else if (input[t->i] == '\0')
	{
		write(2, "msh: parse error\n", ft_strlen("msh: parse error\n"));
		gdata->last_exit_code = 2;
		*token = t->begin;
		return (1);
	}
	else
		add_char(t, input, token);
	t->i++;
	return (0);
}

static int	in_dquot(t_temp *t, char *input, t_list **token)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (input[t->i] == '\"')
	{
		t->state = GENERAL;
		ft_charjoin(&(*token)->data, input[t->i]);
	}
	else if (input[t->i] == '\0')
	{
		write(2, "msh: parse error\n", ft_strlen("msh: parse error\n"));
		gdata->last_exit_code = 127;
		*token = t->begin;
		return (1);
	}
	else
		add_char(t, input, token);
	t->i++;
	return (0);
}

static int	ft_select(t_temp *t, char *input, t_list **token)
{
	if (t->state == GENERAL)
	{
		if (general(t, input, token))
			return (2);
	}
	else if (t->state == IN_QUOT)
	{
		if (in_quot(t, input, token))
			return (1);
	}
	else if (t->state == IN_DQUOT)
	{
		if (in_dquot(t, input, token))
			return (1);
	}
	return (0);
}

int	ft_lexer(char *input, t_list **token)
{
	t_temp	t;
	int		ret;

	t.i = 0;
	t.in_word = 0;
	t.begin = NULL;
	*token = NULL;
	t.state = GENERAL;
	while (1)
	{
		ret = ft_select(&t, input, token);
		if (ret == 1)
			return (1);
		else if (ret == 2)
			break ;
	}
	*token = t.begin;
	if (ft_token_checker(&t.begin, &t))
		return (1);
	return (0);
}
