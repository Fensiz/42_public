/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:47:42 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/11 18:47:44 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == ':' && str[i] != '\0')
		i++;
	while (str[i])
	{
		if (str[i] != ':' && (str[i + 1] == ':' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	*get_path(char *str, int *start)
{
	int		i;
	int		j;
	char	*path;

	j = 0;
	while (str[j] == ':')
		j++;
	if (str[j] == 0)
	{
		*start += j;
		return (NULL);
	}
	i = j;
	while (str[i] != '\0' && str[i] != ':')
		i++;
	path = (char *)malloc((i - j + 2) * sizeof(char));
	if (!path)
		exit(1);
	ft_strlcpy(path, str + j, i - j + 1);
	*(path + i - j) = '/';
	*(path + i - j + 1) = 0;
	if (str[i] == ':')
		i++;
	*start += i;
	return (path);
}

void	parse_path(t_data *data)
{
	char	*path;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = NULL;
	if (data && data->env_parsed)
	{
		path = get_var_value("PATH", data);
		if (path)
		{
			count = get_path_count(path);
			data->path = (char **)malloc((count + 1) * sizeof(char *));
			if (!data->path)
				exit (1);
			data->path[count] = NULL;
			while (j < count)
			{
				data->path[j++] = get_path(&path[i], &i);
			}
		}
	}
}
