# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samjaabo <samjaabo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 08:59:19 by samjaabo          #+#    #+#              #
#    Updated: 2023/04/12 13:37:38 by samjaabo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = program.a
CC = cc
CFLAGS = -Wall -Wextra #-fsanitize=address
export LDFLAGS="-L/Users/samjaabo/.brew/opt/readline/lib"
  export CPPFLAGS="-I/Users/samjaabo/.brew/opt/readline/include"
MAIN_SRC = signals.c main.c lists.c exec.c redirection.c split.c utils.c \
			cmd_path.c translate.c minishell/minishell.c minishell/utils.c minishell/utils2.c \
			minishell/tokenizer.c minishell/tokenizer_utils.c minishell/syntax.c minishell/ft_strjoin.c \
			minishell/ft_memcpy.c minishell/quotes.c minishell/finals_maker.c \
			pipe.c here_doc.c
			
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
		ft_putendl_fd.c ft_strlen.c ft_strchr.c

#src files with path
LIBFT_SRCS = $(addprefix $(LIBFT_DIR),$(LIBFT_FILES))

# object files variables
LIBFT_OBJS =	$(LIBFT_SRCS:%.c=%.o)

all: $(NAME) run

clean:
	@rm -rf $(LIBFT_OBJS) $(MAIN_OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

$(NAME): $(LIBFT_OBJS) $(MAIN_OBJS)
	@ar rc $(NAME) $(LIBFT_OBJS) $(GET_NEXT_LINE_OBJS) $(MAIN_OBJS)

%.o: %.c header.h ./libft/libft.h
	@$(CC) -I/Users/samjaabo/.brew/opt/readline/include $(CFLAGS) -c $< -o $@

run:
	@#@clear
	@$(CC) -L/Users/samjaabo/.brew/opt/readline/lib -lreadline $(CFLAGS) $(NAME) -o  ./tmp/program
	@$(MAKE) fclean
	@#cd tmp
	@#./program
	@#cd ../
	