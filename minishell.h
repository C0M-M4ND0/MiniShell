/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:14:52 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:42:55 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h> 
# include <curses.h>
# include <term.h>

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"

typedef struct s_collect
{
	char	*slash_cmd;
	char	**paths;
	char	**cmd;
}	t_collect;

typedef struct s_global
{
	int	sig_indice;
	int	exit_shell;
	int	exit_code;
}	t_global;

t_global	g_vars;

# define APPEND_MODE 1
# define TRUNC_MODE 0

# define REDIR_TOKEN "minish: syntax error near unexpected token `redirection'"
# define LINE_TOKEN "minish: syntax error near unexpected token `newline'"
# define PARENTH_TOKEN "minish: syntax error near unexpected token `()'"
# define ERR_S_CHAR "minish: syntax error: forbidden special character"
# define MULTI_LINE "minish: syntax error multiple line not allowed"
# define PIPE_TOKEN "minish: syntax error near unexpected token `|'"
# define AND_TOKEN "minish: syntax error near unexpected token `&'"
# define ERR_LOGIC "minish: syntax error: duplicated logic symbols"
# define ERR_PARENTH "minish: syntax error: unclosed parenthesis"
# define ERR_EXIT_ARG "minish: exit: numeric argument required"
# define ERR_QUOTES "minish: syntax error: unclosed quotes"
# define ERR_DIR "minish: unable to read current directory"
# define ERR_EXIT_NUM "minish: exit: too many arguments"
# define UNSET_ARG "minish: unset: invalid identifier"
# define EXP_ARG "minish: export: invalid identifier"
# define ERR_USAGE ": usage: . filename [arguments]"
# define ERR_ARGS ": No such file or directory"
# define CMD_ERROR ": command not found"
# define ERR_PERM ": Permission denied"
# define ERR_ISDIR ": is a directory"

void	init_add_history(char **envp);
void	sig_handel(int signal);
void	add_to_history(char *line, char **envp);
void	add_to_file_history(char *line, char **envp);

void	display_prompt(char	*prompt, char **envp);
char	*readline_config(char *prompt);
void	exit_minish_ctrl_d(char **envp);
void	check_empty_line(void);

void	parse_logic(char *cmds, char **envp);
char	*get_last_cmd(char *cmd, int *logic_opp);
int		check_priorities(char *cmd);
void	parse_input(char *line, char **envp);
int		pipe_parse(char *line, t_list **cmds);

void	to_space(char *str, size_t start, size_t len);
void	remove_quotes_2d(char **strs);
void	remove_quotes_1d(char *str);

char	*expand_cmd(char *line, char **envp);
char	*expand_dollar_symbol(char *line, char **envp);
char	*get_env_var(char *str, char **envp);
char	*get_wildcards_expressions(char *line);
int		examin_entry_name(char *file, char *name);
int		get_l_char_wildcard(char *str);
char	*expand_wildcards(char *name);
int		quoted_wildcard(char *name);

void	free_2d(char **strs);
void	free_res(t_collect *var);
void	exit_error(t_collect *var, char *short_cmd, char *msg, int exit_code);

int		valid_syntax(char *line);
int		check_quotes(char *line);
int		unclosed_quote(char *line);
int		check_val_quotes(char *str);
int		check_parenthesis(char *cmd);
int		check_special_char(char *line);
int		check_genral_syntax(char *str);
int		check_single_quotes(char *line);
int		unclosed_parenthesis(char *line);
int		check_redirection_syntax(char *str);
int		check_valid_parenthesis(char *line);

void	fork_processes(t_list *cmds, char **envp);
int		fork_here_doc(char *cmd, int stdin_dup);
void	fork_child_1(char *cmd, int stdin_dup, int *fd, char **envp);
void	fork_child_2(char *cmd, int stdin_dup, char **envp);
int		execute_fork(char *cmd, int stdin_dup, char **envp);
void	execute_cmd(char *cmd, char **envp);
void	get_exit_code(int pid, int *status);

char	*f_io_names(char *str, int aut);
char	*ft_getenv(char *var, char **envp);
char	*here_doc(char *limiter, int stdin_no);

void	get_here_doc_input(char *cmd, int stdin_dup);
int		open_input_file(char *infile, int stdin_no);
int		open_output_file(char *outfile, int mode);
int		get_io_files(char *cmd, int stdin_no);

int		check_builtin(char *cmd, int stdin_dup, int fd, char **envp);
int		which_builtin(char *args);
void	exit_builtin(int r_builtint);
void	print_envp(char **envp);
void	str_to_lower(char *str);
int		check_num_arg(char c, char *error_msg);
int		update_envp(char *var, char **envp);
void	check_plus(char **var);
void	ft_echo(char **args);
void	ft_cd(char **args, char **envp);
void	ft_pwd(char **args);
void	ft_export(char **args, char **envp);
void	ft_unset(char **args, char **envp);
void	ft_env(char **args, char **envp);
void	ft_exit(char **args, char **envp);
void	free_envp(char **envp);

#endif
