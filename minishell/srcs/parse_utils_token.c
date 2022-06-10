/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 12:55:12 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/09 12:55:14 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*token_create(void)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		exit(1);
	new->data = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type = 0;
	return (new);
}

char	*heredoc_parser(char *str)
{
	char	state;
	char	*new_str;
	int		i;

	i = 0;
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!new_str)
		exit(1);
	state = GENERAL;
	while (*str)
	{
		if (state == GENERAL && *str == '\'')
			state = IN_QUOT;
		else if (state == GENERAL && *str == '\"')
			state = IN_DQUOT;
		else if ((state == IN_QUOT && *str == '\'')
			|| (state == IN_DQUOT && *str == '\"'))
			state = GENERAL;
		else
			new_str[i++] = *str;
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static t_list	*create_at_back(t_list **token_list)
{
	t_list	*curr;

	curr = *token_list;
	if (curr == NULL)
	{
		*token_list = token_create();
		curr = *token_list;
	}
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = token_create();
		curr = curr->next;
	}
	return (curr);
}

t_list	*addback_newtoken(t_list **token_list, t_list *old_token, int type)
{
	t_list	*curr;

	curr = create_at_back(token_list);
	curr->type = old_token->type;
	if (type == REDIRECT && (old_token->type == INPUT
			|| old_token->type == OUTPUT || old_token->type == APPEND))
	{
		if (old_token->next == NULL)
			return (NULL);
		ft_parser(old_token->next, &curr->data);
	}
	else if (type == REDIRECT && old_token->type == HEREDOC)
		curr->data = heredoc_parser(old_token->next->data);
	else if (type == ARGV)
		curr->data = ft_strdup(old_token->data);
	return (curr);
}
