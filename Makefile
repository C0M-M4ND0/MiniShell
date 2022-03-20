# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/18 16:44:11 by eabdelha          #+#    #+#              #
#    Updated: 2022/02/08 10:41:05 by eabdelha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_NAME = libft.a
CURSES_NAME = -lcurses 
READLINE_NAME = -L /goinfre/$(USER)/.brew/opt/readline/lib -lreadline

MAIN_PATH = ./main/
PARSE_PATH = ./parsing/
EXECUTE_PATH = ./execute/
LIBFT_PATH = ./libft/
EXPAND_PATH = ./expand/
BUILTIN_PATH = ./builtin/
GNL_PATH = ./get_next_line/

FOBJ_SRC = object_files

OBJECT_PATH = ./object_files/

INCLUDE = minishell.h
GNL_INCLUDE = $(GNL_PATH)get_next_line.h
RL_INCLUDE = -I /goinfre/eabdelha/.brew/opt/readline/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC	=	minishell.c		\
		prompt.c		\
		history.c		\
		expand_dollar_symbol.c		\
		expand_wildcards_bonus.c			\
		expand_wildcards_utils_bonus.c		\
		logic_opp_bonus.c				\
		logic_opp_utils_bonus.c			\
		parsing.c				\
		valid_syntax.c				\
		syntax_analysis.c			\
		syntax_analysis_utils.c		\
		get_io_files.c		\
		open_io_files.c		\
		here_doc.c			\
		get_here_doc_input.c	\
		parsing_utils.c			\
		free_ressources.c		\
		forc_processes.c		\
		forc_utils.c			\
		execute_cmd.c	\
		check_builtin.c	\
		builtin_utils.c	\
		get_next_line.c			\
		get_next_line_utils.c	\
		ft_echo.c 		\
		ft_cd.c 		\
		ft_pwd.c 		\
		ft_export.c 		\
		ft_export_utils.c	\
		ft_unset.c 		\
		ft_env.c 		\
		ft_exit.c 	

OBJECTS = $(addprefix $(OBJECT_PATH), $(SRC:.c=.o))

.PHONY : all clean fclean re

all: $(NAME)
	@printf "\033[1m\033[33m __  __ _____ _   _ _____  _____ _    _ ______ _      _      \n"
	@printf "|  \/  |_   _| \ |||_   _|/ ____| |  | |  ____| |    | |     \n"
	@printf "| \  / | ||| |  \| | ||| | |___ |||__|||||__  |||    |||     \n"
	@printf "|||\/||| ||| | . \` | |||  \___ \|  __  |  __| |||    |||     \n"
	@printf "|||  |||_|||_|||\  |_|||_ ____| |||  |||||____|||____|||____ \n"
	@printf "|_|  |_|_____|_| \_|_____|_____/|_|  |_|______|______|______|\033[0m\n\n"
 
$(NAME): $(FOBJ_SRC) $(LIBFT_PATH)$(LIBFT_NAME) $(OBJECTS)
	@printf "linking object files...\n"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(READLINE_NAME) $(CURSES_NAME) $(LIBFT_PATH)$(LIBFT_NAME)

$(LIBFT_PATH)$(LIBFT_NAME) : $(LIBFT_NAME)

$(LIBFT_NAME) :
	@make -C $(LIBFT_PATH)

$(OBJECT_PATH)%.o: $(MAIN_PATH)%.c $(INCLUDE)
	$(CC) $(CFLAGS) $(RL_INCLUDE) -o $@ -c $<

$(OBJECT_PATH)%.o: $(PARSE_PATH)%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_PATH)%.o: $(EXECUTE_PATH)%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_PATH)%.o: $(EXPAND_PATH)%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_PATH)%.o: $(BUILTIN_PATH)%.c $(INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_PATH)%.o: $(GNL_PATH)%.c $(GNL_INCLUDE)
	$(CC) $(CFLAGS) -o $@ -c $<

$(FOBJ_SRC) : 
	@mkdir $@

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJECTS)
	@rm -rf $(FOBJ_SRC)

fclean: clean 
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all
