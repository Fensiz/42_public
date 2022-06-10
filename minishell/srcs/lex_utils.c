/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:46:51 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 20:46:53 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_next(t_list **token, t_list **begin)
{
	if (*token == NULL)
	{
		*token = (t_list *)malloc(sizeof(t_list));
		if (*token == NULL)
			exit(1);
		(*token)->prev = NULL;
		(*token)->data = NULL;
		(*token)->next = NULL;
		if (*begin == NULL)
			*begin = *token;
	}
	else
	{
		(*token)->next = (t_list *)malloc(sizeof(t_list));
		if ((*token)->next == NULL)
			exit(1);
		*token = (*token)->next;
		(*token)->data = NULL;
		(*token)->next = NULL;
		(*token)->prev = NULL;
	}
}

int	is_varchar(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| c == '_' || (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

void	ft_numjoin(char **s1, int num)
{
	char	*num_str;
	char	*new_str;

	num_str = NULL;
	new_str = NULL;
	num_str = ft_itoa(num);
	new_str = ft_strjoin(*s1, num_str);
	free(*s1);
	free(num_str);
	*s1 = new_str;
}

char	*ft_get_var_name(char *input, int *i)
{
	char	*var_name;

	var_name = NULL;
	if (input[*i] >= '0' && input[*i] <= '9')
	{
		ft_charjoin(&var_name, input[*i]);
		(*i)++;
	}
	else if (is_varchar(input[*i]))
	{
		while (is_varchar(input[*i]))
		{
			ft_charjoin(&var_name, input[*i]);
			(*i)++;
		}
	}
	else if (input[*i] == '?')
	{
		ft_charjoin(&var_name, input[*i]);
		(*i)++;
	}
	return (var_name);
}

int	ft_token_checker(t_list **token, t_temp *t)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (*token && ((*token)->type == PIPE || (*token)->type == L_OR
			|| (*token)->type == L_AND || lex_token_checker(*token)))
	{
		write(2, "msh: parse error\n", ft_strlen("msh: parse error\n"));
		gdata->last_exit_code = 2;
		*token = t->begin;
		return (1);
	}
	return (0);
}
