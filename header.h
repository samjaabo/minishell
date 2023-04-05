/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:06:58 by samjaabo          #+#    #+#             */
/*   Updated: 2023/04/05 15:18:37 by samjaabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./get_next_line/get_next_line_bonus.h"
# include "./libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include <stdarg.h>
# include <stdint.h>
# include <limits.h>

# include <sys/time.h>
#include <signal.h>
#include <mlx.h>

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
};


typedef struct s_dict {
	struct s_dict	**object;
	struct s_dict	*next;
	char			*key;
	char			*value;
	int				oper;
}	t_dict;

typedef char	t_mallochar;
//utils functions
//utils
int		ft_printf(const char *format, ...);

//===================================
//=============lists.c===============
typedef struct s_cmd {
	// char			*tmp;
	char			**args;
	// char			*key;
	char			**redirs;
	char			**types;
	int				std_in;
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
int		ft_dup_default_stdio(void);

//=============redirection.c===============
int		ft_pipe_in_parent(t_cmd *cmd);
int		ft_pipe_in_child(t_cmd *cmd);
int		ft_file_to_stdin(char *file);
int		ft_here_doc(char *limiter);
int		ft_write_append(char *file);
int		ft_write_truncate(char *file);

//=============split.c===============
char	**ft_mysplit(const char *str, char c);
char	**ft_realloc(char **array, char *new);

//=============utils.c===============
void 	ft_printar(char **t);
void	ft_perror(const char *msg);
void	ft_error(const char *cmd, const char *msg);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);

//=============cmd_path.c===============
t_mallochar	*ft_get_cmd_path(const char *path, const char *cmd);

//=============translate.c===============
t_cmd	*ft_translate(t_list *list);

#endif