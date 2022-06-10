/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:28:22 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 22:28:26 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*try_path(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*dirp;

	dir = opendir(path);
	if (dir)
	{
		dirp = readdir(dir);
		while (dirp)
		{
			if (ft_strcmp(dirp->d_name, name) == 0)
			{
				if (dir)
					closedir(dir);
				return (ft_strjoin(path, name));
			}
			dirp = readdir(dir);
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char	*find_path(char *name)
{
	char		*path;
	int			i;
	t_glob_data	*gdata;

	ft_link(&gdata);
	path = NULL;
	i = 0;
	while (gdata->data->path[i])
	{
		path = try_path(gdata->data->path[i], name);
		if (path)
			return (path);
		i++;
	}
	return (path);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	ft_print_error(int code, char *name)
{
	char	*error;

	if (code < 134)
		error = strerror(code);
	else if (code == 150)
		error = "command not found";
	write(2, "msh: ", ft_strlen("msh: "));
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

char	**ft_env_export(t_env *env)
{
	char	**res;
	char	*temp;
	int		size;
	int		i;

	i = 0;
	size = ft_env_size(env);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		exit(1);
	while (env)
	{
		res[i] = ft_strjoin(env->var_name, "=");
		temp = res[i];
		res[i] = ft_strjoin(res[i], env->value);
		free(temp);
		env = env->next;
		i++;
	}
	res[size] = NULL;
	return (res);
}
