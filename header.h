/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:06:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/18 17:54:40 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include <sys/types.h>
# include <errno.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

// # include <stdint.h>
// # include <limits.h>

#include <signal.h>
#include <sys/stat.h>
#include <termios.h>

typedef struct s_list {
	char			*value;
	int				type;
	struct s_list	*next;
}	t_list;


enum e_constants {
	ERROR = -1,
	NONE = 0,
	FALSE = 0,
	SUCCESS = 0,
	TRUE = 1,
	FAILURE = 2,
	NEW_STDIN=3,
	NEW_STDOU=4,
	NEW_STDER=5,
	HERE_DOCUMENT=2,
	FILE_TO_STDIN=4,
	WRITE_TO_FILE=3,
	APPEND_TO_FILE=1,
	COMMAND_ARG=9,
	COMMAND=9,
	MYFILE=1337,
	PIPE=6,
	STATUS_READIND,
	STATUS_EXECUTING,
	STATUS_HERE_DOC,
	IS_BUILTIN,
};
enum e_exit_codes {
	CMD_NOT_FOUND=127,
	GENERAL_ERROR=1,
	PERMISSION=126,
	INVALID_EXIT_ARG=128,
	EXIT_CODE_OUT_RANGE=255,
	SIGNAL=128,// + siganl number 
};
//=============<GLOBAL>===============
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
	char			*oldpwd;
}	t_data;
//===================================
//===================================
//=============lists.c===============
typedef struct s_cmd {
	char			**args;
	char			**redirs;
	char			**types;
	int				here_doc;
	int				pipe_in;
	int				pipe_out;
	int				id;
	struct s_cmd	*next;
}	t_cmd;

extern t_data	g_data;
//=============lists.c===============
t_cmd	*ft_lstnew(int ids);
void	ft_addlast(t_cmd **head, t_cmd *new);
char	*ft_clear(char **ar);
void	ftx_lstclear(t_cmd **head);

//====================================

//=============exec.c===============
int		ft_redirection(t_cmd *cmd);
int		ft_exec(t_cmd *cmd, char *path);
int		ft_return_default_stdio(void);

//=============pipe.c===============
int		ft_pipe_in_parent(t_cmd *cmd);
int		ft_pipe_in_child(t_cmd *cmd);
int		ft_close_pipe_in_parent(t_cmd *cmd);

//=============here_doc.c===============
int		ft_do_here_doc(t_cmd *cmd);
char	*ft_read(void);

//=============redirection.c===============
int		ft_file_to_stdin(char *file);
int		ft_write_append(char *file);
int		ft_write_truncate(char *file);

//=============split.c===============
char	**ft_mysplit(const char *str, char c);
char	**ft_realloc(char **array, char *new);

//=============utils.c===============
void	ft_init(char **env);
void	ft_exit(void);
int		ft_realloc_fd(int new);
int		ft_copy_env(char **env);
void 	ft_printar(char **t);
void	ft_perror(const char *msg);
void	ft_error(const char *cmd, const char *msg);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);
void	ft_update_prompt_string(void);
char	*ft_readline_nottty(void);

//=============cmd_path.c===============
char	*ft_get_cmd_path(const char *path, const char *cmd);

//=============translate.c===============
t_cmd	*ft_translate(t_list *list);


//=============signals.c.c===============
void	ft_control_d(void);
int		ft_signals(void);
void	ft_control_slash(int sig);

//=============builtins.c===============
void	ft_export(char **args);
void	ft_unset(char **args);
int		ft_isnot_valid_identifier(char *str, char stop);
char	**ft_realloc_env(int ignore);
int		ft_getenv(char *var);
void	ft_echo(char **args);
void	ft_env(char **args);
void	ft_pwd(void);
void	ft_cd(char **args);
int		ft_builtins(t_cmd *cmd);
int		ft_is_builtin(t_cmd *cmd);
void	ft_builtin_exit(char **args);
void	ft_shell_level(void);
int		ft_iscwd_exists(void);
void	ft_init_env(void);

//////tmp///////////////////////////////////////////////////////
typedef struct s_str_len
{
	int	bef;
	int	var;
	int	aft;
}	t_str_len;

char		*get_env(char *var);
char		**split_and_expand(char *str);
int			white_space(char *str);
char		**split_cmd_line(char const *s);
void		expand_variable(char **str, int *i);
int			red_here_doc(char *str);
char		**ft_free(char **str);
void		eliminate_dollar(char **str, int i);

// void		ft_perror(const char *msg);
// int			ft_copy_env(char **env);
// char		**ft_realloc(char **array, char *new);
// char		*ft_clear(char **ar);

/* <<---- PROCESS DATA ---->> */

t_cmd		*process_data(char **splited);
char		*remove_quote(const char *str);

/* <<---- LIBFT ---->> */

// char		*ft_strdup(const char *s1);
// char		*ft_strjoin(char const *s1, char const *s2);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// void		*ft_memcpy(void *dst, const void *src, size_t n);
// size_t		ft_strlen(const char *s);
// int			ft_isalnum(int c);
// int			ft_isalpha(int c);
// int			ft_isdigit(int c);
t_cmd		*ft_lstlast(t_cmd *lst);
// t_cmd		*ft_lstnew(void);
void		ft_lstclear(t_cmd **lst);
void		ft_lstadd_back(t_cmd **lst, t_cmd *new);
int			ft_strcmp(char *s1, char *s2);
// char		*ft_itoa(int n);


#endif