/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:08:55 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:08:56 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handel(int signal)
{
	if ((signal == SIGINT || signal == SIGQUIT) && g_vars.sig_indice)
	{
		printf("\r");
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGINT && g_vars.sig_indice && g_vars.sig_indice != -1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGINT && g_vars.sig_indice == -1)
	{
		g_vars.sig_indice = 0;
		printf("\n");
		exit(1);
	}
}

void	check_empty_line(void)
{
	char			cursor[10];
	int				i;
	int				y;
	struct termios	old;
	struct termios	new;

	ft_bzero(cursor, 10);
	if (tcgetattr(STDIN_FILENO, &old))
		return (perror("tcgetattr"));
	new = old;
	new.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
		return (perror("tcsetattr"));
	i = 0;
	write(0, "\033[6n", 4);
	new.c_cc[VTIME] = 0;
	read(0, cursor, 10);
	while (cursor[i] != ';' && i < 8)
		i++;
	y = ft_atoi(&cursor[i + 1]);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old))
		return (perror("tcsetattr"));
	if (y > 1)
		ft_putstr_fd("\e[30;47m@\e[0m\n", STDOUT_FILENO);
}

int	empty_prompt(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

char	*readline_config(char *prompt)
{
	char			*line;
	struct termios	old;
	struct termios	new;

	if (tcgetattr(STDIN_FILENO, &old))
		perror("tcgetattr");
	new = old;
	new.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
		perror("tcsetattr");
	line = readline(prompt);
	if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old))
		perror("tcsetattr");
	return (line);
}

void	display_prompt(char	*prompt, char **envp)
{
	char	*line;

	signal(SIGINT, sig_handel);
	signal(SIGQUIT, sig_handel);
	init_add_history(envp);
	while (1)
	{
		g_vars.sig_indice = 1;
		line = readline_config(prompt);
		g_vars.sig_indice = 0;
		if (!line)
			exit_minish_ctrl_d(envp);
		if (*line)
			add_to_history(line, envp);
		if (empty_prompt(line))
			;
		else if (valid_syntax(line))
			parse_logic(line, envp);
		else
			g_vars.exit_code = 258;
		free(line);
		if (g_vars.exit_shell != 257)
			exit(g_vars.exit_shell);
	}
}
