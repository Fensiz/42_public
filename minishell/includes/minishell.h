/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bteak <bteak@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:08:29 by bgreenbl          #+#    #+#             */
/*   Updated: 2021/12/14 17:56:42 by bteak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define IN_QUOT 	1
# define IN_DQUOT 	2
# define GENERAL 	0
# define CONTINUE 	3
# define BREAK		2
# define TEXT 		3
# define CMD 		3
# define TEXT_Q 	4
# define TEXT_DQ 	5
# define OUTPUT 	6
# define APPEND 	7
# define INPUT 		8
# define INPUT_D 	9
# define HEREDOC 	9
# define L_AND 		10
# define L_OR 		11
# define PIPE 		12
# define BRC 		13
# define B_OPEN 	13
# define B_CLOSE 	14
# define BUFF_SIZE 	512
# define REDIRECT 	666
# define ARGV 		777
# define CLEAR 		555
# define POP 		557
# define PUSH 		556
# define STAR 		0
# define W_TEXT 	1
# define LAST 		20
# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_fd_stack
{
	int					fd;
	struct s_fd_stack	*next;
}	t_fd_stack;
typedef struct s_list
{
	struct s_list		*next;
	struct s_list		*prev;
	char				*data;
	int					type;
	int					executed;
}	t_list;
typedef struct s_env
{
	struct s_env		*next;
	char				*var_name;
	char				*value;
}	t_env;
typedef struct s_data
{
	int					argc;
	const char			**argv;
	char				**envp;
	t_env				*env_parsed;
	char				**env_tosend;
	char				**path;
	int					last_exit_code;
}	t_data;
typedef struct s_glob_data
{
	int					last_exit_code;
	t_data				*data;
	int					main_proc_mark;
	int					hd;
}	t_glob_data;
typedef struct s_atoi
{
	int					value;
	unsigned char		error;
}	t_atoi;
typedef struct s_temp
{
	t_list				*begin;
	int					i;
	int					in_word;
	char				state;
	char				*res;
}	t_temp;
typedef struct s_cmd_list	t_cmd_list;
typedef struct s_cmd_token	t_cmd_token;
/*
cmd_token - CMD BRC PIPE token list
next - next token list(after && or ||)
*/
typedef struct s_cmd_list
{
	t_cmd_token			*cmd_token;
	t_cmd_list			*next;
	int					logic_mark;
	int					piped;
}	t_cmd_list;
/*
type - CMD|BRC|PIPE
cmd_list - ONLY FOR BRC
argv - ONLY FOR CMD
*/
typedef struct s_cmd_token
{
	int					type;
	t_cmd_list			*cmd_list;
	t_list				*argv;
	t_list				*redirect_list;
	t_cmd_token			*next;
}	t_cmd_token;
/*------------------------ FREE --------------------------------*/
typedef struct s_cmd_token_cmplx
{
	t_cmd_token			*begin;
	t_cmd_token			*curr;
	t_cmd_token			*next;
}t_cmd_token_cmplx;
typedef struct s_cmd_list_cmplx
{
	t_cmd_list			*begin;
	t_cmd_list			*curr;
	t_cmd_list			*next;
}t_cmd_list_cmplx;
typedef struct s_list_cmplx
{
	t_list				*begin;
	t_list				*curr;
	t_list				*next;
}t_list_cmplx;

typedef struct s_complex_return
{
	int					exit_code;
	int					terminate;
	int					ext_code;
	char				*name;
}	t_complex_return;

typedef struct s_exec_info
{
	char				finish_cmd_if_pipe;
	char				finish_br_if_pipe;
	int					pipefd[2];
	int					curr_fd[2];
	int					def_fd[2];
}	t_exec_info;

//extern t_glob_data			g_data;

/* split */
void				*ft_split(void *v_str);
/* ft_itoa */
char				*ft_itoa(int n);
/* utils */
size_t				ft_strlen(const char *s);
char				*ft_strjoin(char *s1, char *s2);
int					ft_charjoin(char **s1, char const c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(char *src);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
/* env */
void				ft_env_parse(t_data *data);
t_env				*ft_env_addnew(int var_name_len, int value_len);
void				ft_env_addback(t_env **env, t_env *new);

void				ft_copy_params(t_data *data, int argc,
						const char **argv, char **envp);
char				*get_var_value(char *var_name, t_data *data);
void				parse_path(t_data *data);

/* executor */
void				ft_executor(t_list **token, t_data *data);

t_list				*token_create(void);
t_list				*ft_lstnew(char *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
int					ft_lstsize(t_list *lst);
int					ft_env_size(t_env *lst);

char				**list_to_argv(t_list *arg);
void				convert_exit_code(t_data *data);
t_complex_return	execute_cmd(t_cmd_token *cmd_token,
						int finish_pipe_child, t_cmd_list *cmd);

t_complex_return	execute_cmd_list(t_cmd_list *cmd_list);
t_complex_return	try_buildin(char **name);
t_atoi				ft_atoi(const char *str, t_atoi result);

void				ft_print_error(int code, char *name);
int					ft_env_size(t_env *begin);
char				**ft_env_export(t_env *env);
/* main_utils */
void				get_line(char **line);
void				sig_void(int signum);
void				sig_handler(int signum);
void				ft_init(t_data *data, int argc,
						const char **argv, char **envp);
void				var_init(t_complex_return *ret, t_list **token);
/* free */
void				free_env(void);
void				free_path(void);
void				free_tokens(t_list **token);
void				free_cmd_content(t_cmd_token *data);
void				free_cmd_token_list(t_cmd_token **data);
void				free_cmd_list(t_cmd_list **data);
void				free_argv(char **argv);

int					is_buildin(char *cmd_token);
void				split_arg_to_args(t_list *arg, t_list **arg_new);
void				ft_list_dup(t_list *lst, t_list **n_lst);
int					check_cmd_list(t_cmd_list *cmd_list);
/*			LEXER			*/
/* lexer_main */
int					ft_lexer(char *input, t_list **token);
/* lexer_general */
int					general(t_temp *t, char *input, t_list **token);
/* lex_utils */
void				ft_create_next(t_list **token, t_list **begin);
int					is_varchar(int c);
void				ft_numjoin(char **s1, int num);
char				*ft_get_var_name(char *input, int *i);
int					ft_token_checker(t_list **token, t_temp *t);
/* lex_finisher_main */
int					ft_parser(t_list *token, char **new_res);
/* lex_finisher */
int					lex_fin_select(t_temp *t, char *input);
/*			PARSER			*/
/* split_cmd */
int					split_cmd(t_list *curr, t_cmd_list **cmd_list);
/* token */
t_list				*token_create(void);
t_list				*addback_newtoken(t_list **token_list,
						t_list *old_token, int type);
/* cmd_token */
t_cmd_token			*cmd_token_create(void);
t_cmd_token			*addback_new_cmdtoken(t_cmd_token **cmd_token, int type);
/* cmd_list */
t_cmd_list			*cmd_list_create(void);
t_cmd_list			*addback_new_cmdlist(t_cmd_list **cmd_list, int logic_mark);
/*			EXECUTE			*/
/* exec_utils */
void				g_convert_exit_code(void);
char				**list_to_argv(t_list *arg);
/* exec_utils_2 */
char				*try_path(char *path, char *name);
char				*find_path(char *name);
int					is_directory(const char *path);
void				ft_print_error(int code, char *name);
char				**ft_env_export(t_env *env);
/* star_find_file */
t_list				*find_file(char *file_pattern, t_list **token_list);
/* star */
void				split_arg_to_args(t_list *arg, t_list **arg_new);
void				ft_list_dup(t_list *lst, t_list **n_lst);
/* exec_apply_1 */
void				apply_tilda(t_list *curr);
pid_t				apply_pipe(int *curr_fd);
int					apply_output_token(t_list **rdr_token);
/* exec_apply_2 */
int					apply_redirect_token(t_cmd_token *cmd_token);
/* exec_cmd_token_list */
int					exec_cmd_token_list(t_exec_info *info,
						t_cmd_list *curr_cmd_list, t_complex_return *ret);
/* exec_cmd_list */
t_complex_return	execute_cmd_list(t_cmd_list *cmd_list);
/* exec_cmd_list_check */
int					check_cmd_list(t_cmd_list *cmd_list);
/* exec_cmd_utils */
int					exec_fork(t_cmd_token *cmd_token,
						char **argv, t_cmd_list *cmd, t_complex_return *code);
void				ft_ret(char **argv, t_complex_return *code,
						int ret, char **env_tosend);
void				ret_set(int *ret, int err);
void				exec_main(char **argv, char ***path_in,
						char **env_tosend, int *ret);
void				modif_arg(t_complex_return *code, char ***argv,
						t_cmd_token *cmd_token, t_data **data);
/* fd_mem */
int					fd_mem(int fd, int action);
/* builtins */
int					cd_cmd(char **args);
void				unset_cmd(char **argv);
void				echo_cmd(char **argv);
int					pwd_cmd(void);
void				export_cmd(char **argv);
void				env_cmd(void);
int					exit_cmd(char **argv);

char				*get_env(char *argv);
int					set_env(char *env, char *value);
int					is_valid_env(char *str);
void				export_no_args(void);
void				export_params(char **params);
void				add_new_env(char **params);
void				ft_env_clear(t_env **lst);
void				ft_sort_list(t_env **begin_list, int (*cmp)());

void				log_error(char *name);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr(char *s);
void				ft_putchar(char c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);

int					fd_mem(int fd, int action);
void				sig_void(int signum);
int					lex_token_checker(t_list *token);
void				ft_strjoin_n_free(char **output, char *input);
int					ft_isspace(int c);
void				ft_link(t_glob_data **export);
void				sig_void2(int signum);
void				fd_close(t_cmd_list *cmd);
#endif
