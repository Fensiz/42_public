/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:53:55 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/14 17:37:00 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	all_free(char **input, t_list **tokens, t_complex_return *ret)
{
	t_glob_data	*gdata;

	ft_link(&gdata);
	free_tokens(tokens);
	free(*input);
	free_env();
	free_path();
	if (gdata->main_proc_mark)
		write(1, "exit\n", 5);
	exit(ret->exit_code);
}

static void	token_handle(t_list	**tokens, t_complex_return *ret, char **input)
{
	t_cmd_list			*cmd_list;

	if (*tokens)
	{
		signal(SIGINT, sig_void);
		if (!split_cmd(*tokens, &cmd_list))
		{
			if (check_cmd_list(cmd_list))
			{
				write(2, "msh: parsing error\n",
					ft_strlen("msh: parsing error\n"));
				ret->exit_code = 2;
			}
			else
				*ret = execute_cmd_list(cmd_list);
			free_cmd_list(&cmd_list);
			fd_mem(0, CLEAR);
			if (ret->terminate)
				all_free(input, tokens, ret);
		}
		signal(SIGINT, sig_handler);
	}
}

static void	main_hlp(char **input)
{
	*input = (char *)malloc(5 * sizeof(char));
	if (!*input)
		exit(1);
	ft_strlcpy(*input, "exit", 5);
}

int	main(int argc, const char **argv, char **envp)
{
	char				*input;
	t_list				*tokens;
	t_data				data;
	t_complex_return	ret;

	ft_init(&data, argc, argv, envp);
	input = NULL;
	while (1)
	{
		var_init(&ret, &tokens);
		get_line(&input);
		if (!input)
			main_hlp(&input);
		if (!ft_lexer(input, &tokens))
			token_handle(&tokens, &ret, &input);
		free_tokens(&tokens);
	}
	return (0);
}
