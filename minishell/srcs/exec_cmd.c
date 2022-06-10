/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:21:22 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/12 19:36:45 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ec_hlp(char **argv, t_complex_return *code, int term, int ec)
{
	free_argv(argv);
	code->terminate = term;
	code->exit_code = ec;
}

static int	func(t_complex_return *buildin, char **argv)
{
	*buildin = try_buildin(argv);
	return (is_buildin(argv[0]));
}

static void	close_stdin(t_complex_return *buildin, t_complex_return *code)
{
	close(0);
	while (wait(NULL) != -1)
		;
	code->exit_code = buildin->exit_code;
}

static void	exec_func(char **argv, t_complex_return *code)
{
	t_data		*data;
	int			ret;
	t_glob_data	*gdata;

	ft_link(&gdata);
	data = gdata->data;
	ret = 0;
	data->env_tosend = ft_env_export(data->env_parsed);
	exec_main(argv, &data->path, data->env_tosend, &ret);
	ft_ret(argv, code, ret, data->env_tosend);
}

t_complex_return	execute_cmd(t_cmd_token *cmd_token,
						int finish_pipe_child, t_cmd_list *cmd)
{
	char				**argv;
	t_data				*data;
	t_complex_return	buildin;
	t_complex_return	code;

	modif_arg(&code, &argv, cmd_token, &data);
	if (argv[0])
	{
		if (func(&buildin, argv))
			close_stdin(&buildin, &code);
		if (buildin.exit_code == -1)
		{
			if (!finish_pipe_child)
				if (exec_fork(cmd_token, argv, cmd, &code))
					return (code);
			exec_func(argv, &code);
		}
		else if (finish_pipe_child || buildin.terminate || cmd->piped)
			ec_hlp(argv, &code, 1, buildin.exit_code);
		else
			ec_hlp(argv, &code, 0, buildin.exit_code);
	}
	else
		ec_hlp(argv, &code, 0, 0);
	return (code);
}
