/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:43:15 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 20:43:18 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_n_br_handle(t_temp *t, char *input, t_list **token)
{
	ft_create_next(token, &t->begin);
	t->in_word = 0;
	if (input[t->i] == '(')
		(*token)->type = B_OPEN;
	else if (input[t->i] == ')')
		(*token)->type = B_CLOSE;
	else if (input[t->i] == '>')
	{
		(*token)->type = OUTPUT;
		if (input[t->i + 1] == '>')
		{
			(*token)->type = APPEND;
			t->i++;
		}
	}
	else if (input[t->i] == '<')
	{
		(*token)->type = INPUT;
		if (input[t->i + 1] == '<')
		{
			(*token)->type = INPUT_D;
			t->i++;
		}
	}
}

static void	meet_quotes(t_temp *t, char *input, t_list **token)
{
	if (input[t->i] == '\'')
		t->state = IN_QUOT;
	else
		t->state = IN_DQUOT;
	if (t->in_word == 0)
	{
		ft_create_next(token, &t->begin);
		(*token)->type = TEXT;
		t->in_word++;
	}
	ft_charjoin(&(*token)->data, input[t->i]);
}

static void	meet_others(t_temp *t, char *input, t_list **token)
{
	if (t->in_word == 0)
	{
		ft_create_next(token, &t->begin);
		(*token)->type = TEXT;
	}
	ft_charjoin(&(*token)->data, input[t->i]);
	t->in_word++;
}

static void	meet_separator(t_temp *t, char *input, t_list **token)
{
	if (ft_strncmp(&input[t->i], "&&", 2) == 0)
	{
		ft_create_next(token, &t->begin);
		(*token)->type = L_AND;
		t->in_word = 0;
		t->i++;
	}
	else if (ft_strncmp(&input[t->i], "||", 2) == 0)
	{
		ft_create_next(token, &t->begin);
		(*token)->type = L_OR;
		t->in_word = 0;
		t->i++;
	}
}

int	general(t_temp *t, char *input, t_list **token)
{
	if (input[t->i] == '\'' || input[t->i] == '\"')
		meet_quotes(t, input, token);
	else if (input[t->i] == '(' || input[t->i] == ')'
		|| input[t->i] == '>' || input[t->i] == '<')
		redir_n_br_handle(t, input, token);
	else if (ft_strncmp(&input[t->i], "&&", 2) == 0
		|| ft_strncmp(&input[t->i], "||", 2) == 0)
		meet_separator(t, input, token);
	else if (input[t->i] == '|')
	{
		ft_create_next(token, &t->begin);
		(*token)->type = PIPE;
		t->in_word = 0;
	}
	else if (input[t->i] == '\0')
		return (1);
	else if (ft_isspace(input[t->i]))
	{
		if (t->in_word != 0)
			t->in_word = 0;
	}
	else
		meet_others(t, input, token);
	t->i++;
	return (0);
}
