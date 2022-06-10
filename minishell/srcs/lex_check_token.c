/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 11:34:40 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/12 11:34:42 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_token_checker(t_list *token)
{
	while (token)
	{
		if (token && (token->type == INPUT || token->type == OUTPUT
				|| token->type == APPEND || token->type == HEREDOC
				|| token->type == L_AND || token->type == L_OR
				|| token->type == PIPE) && token->next
			&& (token->next->type == INPUT || token->next->type == OUTPUT
				|| token->next->type == APPEND || token->next->type == HEREDOC
				|| token->next->type == L_AND || token->next->type == L_OR
				|| token->next->type == PIPE))
			return (1);
		else if (token && (token->type == B_OPEN)
			&& token->next == NULL)
			return (1);
		else if (token && (token->type == INPUT || token->type == OUTPUT
				|| token->type == APPEND || token->type == HEREDOC
				|| token->type == L_AND || token->type == L_OR
				|| token->type == PIPE) && token->next == NULL)
			return (1);
		token = token->next;
	}
	return (0);
}
