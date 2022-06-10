/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:49:02 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/11 18:49:03 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_params(t_data *data, int argc, const char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->env_tosend = NULL;
	data->env_parsed = NULL;
	data->path = NULL;
	data->last_exit_code = 0;
}

void	ft_env_addback(t_env **env, t_env *new)
{
	t_env	*curr;

	curr = *env;
	if (curr == NULL)
		*env = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_env	*ft_env_addnew(int var_name_len, int value_len)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit(1);
	new->value = (char *)malloc((value_len + 1) * sizeof(char));
	new->var_name = (char *)malloc((var_name_len + 1) * sizeof(char));
	if (!new->value || !new->var_name)
		exit(1);
	new->next = NULL;
	return (new);
}

void	ft_env_parse(t_data *data)
{
	int		i;
	int		j;
	int		k;
	t_env	*env;

	i = 0;
	if (data->envp)
	{
		while (data->envp[i])
		{
			j = 0;
			while (data->envp[i][j] != '=')
				j++;
			k = 0;
			while (data->envp[i][k + j + 1])
				k++;
			env = ft_env_addnew(j, k);
			ft_strlcpy(env->var_name, *(data->envp + i), j + 1);
			ft_strlcpy(env->value, *(data->envp + i) + j + 1, k + 1);
			ft_env_addback(&data->env_parsed, env);
			env = NULL;
			i++;
		}
	}
}

char	*get_var_value(char *var_name, t_data *data)
{
	t_env	*env;

	env = data->env_parsed;
	while (env)
	{
		if (ft_strcmp(var_name, env->var_name) == 0)
			break ;
		env = env->next;
	}
	if (env)
		return (env->value);
	return (NULL);
}
