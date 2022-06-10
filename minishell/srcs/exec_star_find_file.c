/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_star_find_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:26:08 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 14:26:09 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*custom_dup(char **str)
{
	char	*curr;
	int		i;
	char	*new;

	i = 0;
	curr = *str;
	while (curr[i] != 0 && curr[i] != -120)
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (!new)
		exit(1);
	new[i] = 0;
	i = 0;
	while (curr[i] != 0 && curr[i] != -120)
	{
		new[i] = curr[i];
		i++;
	}
	(*str) += i;
	return (new);
}

static void	create_w_token(t_list **token, char **pos, int type)
{
	t_list	*new;

	new = token_create();
	ft_lstadd_back(token, new);
	new->type = type;
	if (type == W_TEXT)
		new->data = custom_dup(pos);
	else
	{
		while (**pos == -120)
			(*pos)++;
	}
}

static t_list	*split_arg(char *arg)
{
	int		i;
	t_list	*new;
	char	*curr;

	i = 0;
	new = NULL;
	curr = arg;
	while (*curr)
	{
		if (*curr == -120)
			create_w_token(&new, &curr, STAR);
		else
			create_w_token(&new, &curr, W_TEXT);
	}
	return (new);
}

static int	check_name(char *name, t_list *wildcard)
{
	int	i;

	i = 0;
	while (wildcard)
	{
		if (wildcard->type == STAR && wildcard->next == NULL)
			return (1);
		else if (wildcard->type == W_TEXT && name[i])
		{
			if (ft_strncmp(wildcard->data, &name[i],
					ft_strlen(wildcard->data)) != 0)
				return (0);
			i += ft_strlen(wildcard->data);
			wildcard = wildcard->next;
		}
		else if (wildcard->type == STAR && wildcard->next != NULL)
		{
			wildcard = wildcard->next;
			while (name[i] && name[i] != wildcard->data[0])
				i++;
			if (!name[i])
				return (0);
		}
	}
	return (1);
}

t_list	*find_file(char *file_pattern, t_list **token_list)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*wild_card;
	t_list			*new_token;

	new_token = NULL;
	wild_card = split_arg(file_pattern);
	dir = opendir("./");
	if (!dir)
		exit(1);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, "..") && entry->d_name[0] != '.'
			&& check_name(entry->d_name, wild_card))
		{
			new_token = token_create();
			new_token->data = ft_strdup(entry->d_name);
			ft_lstadd_back(token_list, new_token);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	free_tokens(&wild_card);
	return (new_token);
}
