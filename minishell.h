/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araqioui <araqioui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:06:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/21 14:07:25 by araqioui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include <signal.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_list {
	char			*value;
	int				type;
	struct s_list	*next;
}	t_list;

enum e_constants {
	ERROR = -1,
	FALSE = 0,
	SUCCESS = 0,
	TRUE = 1,
	HERE_DOCUMENT=2,
	FILE_TO_STDIN=4,
	WRITE_TO_FILE=3,
	APPEND_TO_FILE=1,
	STATUS_READIND,
	STATUS_EXECUTING,
	STATUS_HERE_DOC,
};

enum e_exit_codes {
	CMD_NOT_FOUND=127,
	GENERAL_ERROR=1,
	PERMISSION=126,
	INVALID_EXIT_ARG=128,
	EXIT_CODE_OUT_RANGE=255,
};

typedef struct s_data {
	char			**env;
	int				status;
	int				exit_status;
	int				new_stdin;
	int				new_stdout;
	int				default_path;
	volatile int	here_doc_control_c;
	char			*succ_str;
	char			*fail_str;
}	t_data;

typedef struct s_cmd {
	char			**args;
	char			**redirs;
	char			**types;
	char			**quote;
	int				here_doc;
	int				pipe_in;
	int				pipe_out;
	int				id;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_str_len
{
	int	bef;
	int	var;
	int	aft;
}	t_str_len;

extern t_data	g_data;

void	ft_print_signal(void);
void	ft_addlast(t_cmd **head, t_cmd *new);
void	ftx_lstclear(t_cmd **head);
int		ft_redirection(t_cmd *cmd);
int		ft_exec(t_cmd *cmd, char *path);
int		ft_return_default_stdio(void);
int		ft_pipe_in_parent(t_cmd *cmd);
int		ft_pipe_in_child(t_cmd *cmd);
int		ft_close_pipe_in_parent(t_cmd *cmd);
int		ft_do_here_doc(t_cmd *cmd);
int		ft_file_to_stdin(char *file);
int		ft_write_append(char *file);
int		ft_write_truncate(char *file);
void	ft_init(char **env);
void	ft_exit(void);
int		ft_realloc_fd(int new);
int		ft_copy_env(char **env);
void	ft_perror(const char *msg);
void	ft_error(const char *cmd, const char *msg);
void	ft_update_prompt_string(void);
void	ft_control_d(void);
int		ft_signals(void);
void	ft_control_slash(int sig);
int		ft_exec_builtins(t_cmd *cmd);
void	ft_export(char **args);
void	ft_unset(char **args);
int		ft_isnot_valid_identifier(char *str, char stop);
int		ft_getenv(char *var);
void	ft_echo(char **args);
void	ft_env(char **args);
void	ft_pwd(int n);
void	ft_cd(char **args);
int		ft_builtins(t_cmd *cmd);
int		ft_is_builtin(t_cmd *cmd);
void	ft_builtin_exit(char **args, t_cmd **cmd);
void	ft_shell_level(void);
int		ft_iscwd_exists(void);
void	ft_init_env(void);
void	ft_update_oldpwd(void);
void	ft_update_pwd(void);
void	ft_update_lastcmd(char **args);
void	selection_sort_vars(void);
void	selection_sort(char **env, int len);
void	export(char **args);
int		valid_var(char *str);
void	expand_variable(char **str, int *i);
void	find_variable(char **str, int hd, int i);
void	var_special_case(char **str);
int		check_var_quotes(char *str, int *qu);
void	fill_the_list(t_cmd **lst, char **str, int i, int j);
void	classing_files(t_cmd **ptr, char *str, int qu);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
int		ft_strcmp(char *s1, char *s2);
char	**ft_realloc_env(int ignore);
char	**ft_realloc(char **array, char *new);
char	**syntax_and_split(char *str);
char	**split_cmd_line(char const *s);
char	*get_env(char *var);
t_cmd	*ft_lstlast(t_cmd *lst);
t_cmd	*ft_lstnew(int ids);
char	*ft_read(void);
char	*ft_clear(char **ar);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
char	*ft_get_cmd_path(const char *path, const char *cmd);
char	*rm_quote(char **str, int i, int j);
t_cmd	*process_data(char **splited);
void	fill_args(t_cmd **ptr, char **str);
void	put_quotes(char **str, int nb_q);
int		ft_space(char c);

#endif