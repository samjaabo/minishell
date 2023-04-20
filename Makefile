# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 08:59:19 by samjaabo          #+#    #+#              #
#    Updated: 2023/04/20 21:51:59 by samjaabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = program.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address

MAIN_SRC = signals.c main.c lists.c exec.c redirection.c utils.c \
			cmd_path.c builtin_utils.c \
			pipe.c here_doc.c env_default.c \
			export.c selection_sort.c \
			builtin_cd.c builtin_echo.c builtin_env.c builtin_export.c builtin_pwd.c builtin_unset.c builtin_exit.c \
			expand_var.c find_var.c quot_pipe_red.c split_cmd_line.c \
			fill_the_list.c proc_data.c remove_quotes.c \
			
MAIN_OBJS = $(MAIN_SRC:.c=.o)
# directory variables
LIBFT_DIR = ./libft/

#src files
LIBFT_FILES = ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c \
		ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_bzero.c ft_strrchr.c ft_strnstr.c \
		ft_strlcpy.c ft_strlcat.c ft_strncmp.c \
		ft_itoa.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strtrim.c ft_split.c ft_strmapi.c \
		ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_strlen.c ft_strchr.c ft_strcmp.c \

#src files with path
LIBFT_SRCS = $(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

# object files variables
LIBFT_OBJS =	$(LIBFT_SRCS:%.c=%.o)

INCLUDE_PATH = -I/Users/samjaabo/.brew/opt/readline/include
READLINE_PATH = -L/Users/samjaabo/.brew/opt/readline/lib

all: $(NAME) run

clean:
	@rm -rf $(LIBFT_OBJS) $(MAIN_OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

$(NAME): $(LIBFT_OBJS) $(MAIN_OBJS)
	@ar rc $(NAME) $(LIBFT_OBJS) $(MAIN_OBJS)

%.o: %.c header.h ./libft/libft.h
	@$(CC) $(INCLUDE_PATH) $(CFLAGS) -c $< -o $@

run:
	@$(CC) $(READLINE_PATH) -lreadline $(CFLAGS) $(NAME) -o  program
	@$(MAKE) fclean
	@env -i ./program
	