/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_finisher_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:21:47 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 22:21:49 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_list *token, char **new_res)
{
	char	*input;
	t_temp	t;
	int		ret;

	t.res = NULL;
	input = token->data;
	t.i = 0;
	t.state = GENERAL;
	token->data = NULL;
	while (1)
	{
		ret = lex_fin_select(&t, input);
		if (ret == 2)
			break ;
	}
	*new_res = t.res;
	free(input);
	return (0);
}
