/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:23:46 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/10 22:23:51 by bgreenbl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_fork(t_cmd_token *cmd_token, char **argv, t_cmd_list *cmd,
		t_complex_return *code)
{
	pid_t		pid;
	t_glob_data	*gdata;

	ft_link(&gdata);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid)
	{
		if (cmd_token->next == NULL)
		{
			fd_close(cmd);
			waitpid(pid, &gdata->last_exit_code, 0);
			while (wait(NULL) != -1)
				;
			g_convert_exit_code();
			free_argv(argv);
		}
		code->terminate = cmd->piped;
		code->exit_code = gdata->last_exit_code;
		return (1);
	}
	else
		gdata->main_proc_mark = 0;
	return (0);
}

void	ft_ret(char **argv, t_complex_return *code, int ret, char **env_tosend)
{
	if (ret == -1)
	{
		ft_print_error(errno, argv[0]);
		free_argv(argv);
		free_argv(env_tosend);
		code->terminate = 1;
		if (errno == 13)
			code->exit_code = 126;
		else
			code->exit_code = 127;
	}
	else
	{
		free_argv(argv);
		code->terminate = 1;
		code->exit_code = 0;
	}
}

void	ret_set(int *ret, int err)
{
	*ret = -1;
	errno = err;
}

void	exec_main(char **argv, char ***path_in, char **env_tosend, int *ret)
{
	char	*path;

	path = NULL;
	if (**argv != '/' && **argv != '.')
	{
		if (*path_in)
			path = find_path(argv[0]);
		if (path)
			*ret = execve(path, argv, env_tosend);
		else
			ret_set(ret, 150);
		free(path);
	}
	else
	{
		if (is_directory(argv[0]))
			ret_set(ret, 21);
		else
			*ret = execve(argv[0], argv, env_tosend);
	}
}

void	modif_arg(t_complex_return *code, char ***argv, t_cmd_token *cmd_token,
			t_data **data)
{
	t_list		*temp;
	t_glob_data	*gdata;

	ft_link(&gdata);
	code->exit_code = 0;
	code->terminate = 0;
	*data = gdata->data;
	ft_list_dup(cmd_token->argv, &temp);
	split_arg_to_args(temp, &temp);
	apply_tilda(temp);
	*argv = list_to_argv(temp);
	free_tokens(&temp);
}
