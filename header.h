/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:06:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/12 16:31:41 by samjaabo         ###   ########.fr       */
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
};

//=============<GLOBAL>===============
typedef struct s_data {
	char			**env;
	int				status;
	int				exit_status;
	int				new_stdin;
	int				new_stdout;
	int				new_stderr;
	int				pipe_old;
	int				pipe_in;
	int				pipe_out;
	int				*here_doc;
	volatile int	control;
	volatile int	here_doc_control_c;
	char			*succ_str;
	char			*fail_str;
}	t_data;
//===================================

//===================================
//=============lists.c===============
typedef struct s_cmd {
	// char			*tmp;
	char			**args;
	// char			*key;
	char			**redirs;
	char			**types;
	int				here_doc;
	int				std_out;
	int				id;
	struct s_cmd	*next;
}	t_cmd;

//=============lists.c===============
t_cmd	*ft_lstnew(int ids);
void	ft_addlast(t_cmd **head, t_cmd *new);
char	*ft_clear(char **ar);
void	ftx_lstclear(t_cmd **head);
void	ft_printcmd(t_cmd *head);
//====================================

//=============exec.c===============

int		ft_exec(t_cmd *cmd, char *path, char **env);
int		ft_return_default_stdio(void);

//=============pipe.c===============
int		ft_pipe_in_parent(t_cmd *cmd);
int		ft_pipe_in_child(t_cmd *cmd);
int		ft_close_pipe_in_parent(t_cmd *cmd);

//=============here_doc.c===============
int		ft_do_here_doc(t_cmd *cmd);

//=============redirection.c===============
int		ft_file_to_stdin(char *file);
int		ft_write_append(char *file);
int		ft_write_truncate(char *file);

//=============split.c===============
char	**ft_mysplit(const char *str, char c);
char	**ft_realloc(char **array, char *new);

//=============utils.c===============
void	ft_init(void);
void	ft_exit(void);
int		ft_realloc_fd(int new);
int		ft_close_fds(void);
void 	ft_printar(char **t);
void	ft_perror(const char *msg);
void	ft_error(const char *cmd, const char *msg);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);

//=============cmd_path.c===============
char	*ft_get_cmd_path(const char *path, const char *cmd);

//=============translate.c===============
t_cmd	*ft_translate(t_list *list);


//=============signals.c.c===============
void	ft_control_d(void);
int		ft_signals(void);
void	ft_control_slash(int sig);
//////tmp
t_cmd	*body(char *line);

char    *prompt(int exit_status, char *succ, char *fail);

#endif