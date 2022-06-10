/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_finisher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:20:56 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 22:20:58 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_quot(t_temp *t, char *input)
{
	if (input[t->i] == '\'')
		t->state = GENERAL;
	else if (input[t->i] == '\0')
		return (2);
	else
		ft_charjoin(&t->res, input[t->i]);
	t->i++;
	return (0);
}

static void	bucks(t_temp *t, char *input)
{
	char		*var_name;
	t_glob_data	*gdata;

	ft_link(&gdata);
	t->i++;
	var_name = ft_get_var_name(input, &t->i);
	if (!var_name)
		ft_charjoin(&t->res, '$');
	else if (ft_strcmp(var_name, "?") == 0)
		ft_numjoin(&t->res, gdata->last_exit_code);
	else if (*var_name >= '0' && *var_name <= '9')
	{
		if ((int)*var_name - '0' < gdata->data->argc)
			ft_strjoin_n_free(&t->res,
				(char *)gdata->data->argv[(int)*var_name - '0']);
		else if (t->res == NULL)
			t->res = ft_strdup("");
	}
	else
		ft_strjoin_n_free(&t->res, get_var_value(var_name, gdata->data));
	free(var_name);
}

static int	in_dquot(t_temp *t, char *input)
{
	if (input[t->i] == '\"')
		t->state = GENERAL;
	else if (input[t->i] == '\0')
		return (BREAK);
	else if (input[t->i] == '$')
	{
		bucks(t, input);
		return (CONTINUE);
	}
	else
		ft_charjoin(&t->res, input[t->i]);
	t->i++;
	return (0);
}

static int	lex_fin_general(t_temp *t, char *input)
{
	if (input[t->i] == '\'')
	{
		t->state = IN_QUOT;
		if (t->res == NULL)
			t->res = ft_strdup("");
	}
	else if (input[t->i] == '\"')
	{
		t->state = IN_DQUOT;
		if (t->res == NULL)
			t->res = ft_strdup("");
	}
	else if (input[t->i] == '$')
	{
		bucks(t, input);
		return (CONTINUE);
	}
	else if (input[t->i] == '*')
		ft_charjoin(&t->res, -120);
	else if (input[t->i] == '\0')
		return (BREAK);
	else
		ft_charjoin(&t->res, input[t->i]);
	t->i++;
	return (0);
}

int	lex_fin_select(t_temp *t, char *input)
{
	if (t->state == GENERAL)
		return (lex_fin_general(t, input));
	else if (t->state == IN_QUOT)
		return (in_quot(t, input));
	else if (t->state == IN_DQUOT)
		return (in_dquot(t, input));
	return (0);
}
