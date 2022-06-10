/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:16:39 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/11 20:18:22 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	*line = readline("minishell> ");
	if (*line && ft_strlen(*line))
		add_history(*line);
}

void	sig_void(int signum)
{
	(void)signum;
}

void	sig_handler(int signum)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		gdata->last_exit_code = 1;
	}
}

void	ft_init(t_data *data, int argc, const char **argv, char **envp)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	gdata->last_exit_code = 0;
	gdata->main_proc_mark = 1;
	ft_copy_params(data, argc, argv, envp);
	ft_env_parse(data);
	parse_path(data);
	gdata->data = data;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
}

void	var_init(t_complex_return *ret, t_list **token)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	ret->terminate = 0;
	ret->exit_code = 0;
	*token = NULL;
	rl_catch_signals = 0;
	gdata->hd = 0;
}
