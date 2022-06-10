/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 21:51:50 by bteak             #+#    #+#             */
/*   Updated: 2021/12/15 16:50:57 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_params(char **params)
{
	int			i;
	t_glob_data	*gdata;

	ft_link(&gdata);
	add_new_env(params);
	if (ft_strcmp(params[0], "PATH") == 0)
	{
		free_path();
		parse_path(gdata->data);
	}
	i = 0;
	while (i < 2)
	{
		if (params[i] != NULL)
		{
			free(params[i]);
			params[i] = NULL;
		}
		i++;
	}
}

static int	check_params(char **params)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (!is_valid_env(params[0]))
	{
		if (params[0])
		{
			ft_putstr_fd("msh: export: `", 2);
			ft_putstr_fd(params[0], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			gdata->last_exit_code = 1;
			free(params[0]);
		}
		if (params[1])
			free(params[1]);
		return (1);
	}
	return (0);
}

static void	write_export_args(char *str, char **params, int i)
{
	int	j;

	j = 0;
	params[0] = malloc(sizeof(char) * (i + 1));
	if (!params[0])
		exit(1);
	ft_strlcpy(params[0], str, i + 1);
	j = (int)ft_strlen(str + i);
	params[1] = malloc (sizeof(char) * (j + 1));
	if (!params[1])
	{
		free(params[0]);
		exit(1);
	}
	ft_strlcpy(params[1], str + i + 1, j + 1);
}

static int	get_args(char *str, char **params)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		write_export_args(str, params, i);
	else
	{
		if (get_env(str))
			return (1);
		params[0] = malloc(sizeof(char) * (i + 1));
		if (!params[0])
			exit(1);
		ft_strlcpy(params[0], str, i + 1);
		params[1] = malloc (sizeof(char));
		if (!params[1])
		{
			free(params[0]);
			exit(1);
		}
		ft_strlcpy(params[1], "\0", 1);
	}
	return (check_params(params));
}

void	export_cmd(char **argv)
{
	char		*new_param[2];
	int			i;
	t_glob_data	*gdata;

	ft_link(&gdata);
	new_param[0] = NULL;
	new_param[1] = NULL;
	gdata->last_exit_code = 0;
	if (!argv[1])
	{
		export_no_args();
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (!get_args(argv[i], new_param))
			export_params(new_param);
		i++;
	}
}
