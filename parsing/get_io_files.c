/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:22 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:24 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_f_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

int	get_l_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '<'
		&& str[i] != '>')
	{
		i += check_quotes(&str[i]);
		i++;
	}
	return (i);
}

char	*f_io_names(char *str, int aut)
{
	int		i;
	int		j;
	int		start;
	char	*file_name;

	i = 0;
	j = 0;
	file_name = NULL;
	j = get_f_char(&str[i]);
	start = i + j;
	i = get_l_char(&str[start]);
	if (aut)
	{
		file_name = ft_substr(str, start, i);
		remove_quotes_1d(file_name);
	}
	to_space(str, start, i);
	return (file_name);
}

int	get_io_files(char *cmd, int stdin_no)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i += check_quotes(&cmd[i]);
		if (cmd[i] == '<' && cmd[i + 1] != '<')
			return (to_space(cmd, i, 1),
				open_input_file(f_io_names(&cmd[i + 1], 1), stdin_no));
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
			return (to_space(cmd, i, 2),
				open_input_file(ft_strdup(".heredoc.tmp"), stdin_no));
		else if (cmd[i] == '>' && cmd[i + 1] != '>')
			return (to_space(cmd, i, 1),
				open_output_file(f_io_names(&cmd[i + 1], 1), TRUNC_MODE));
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
			return (to_space(cmd, i, 2),
				open_output_file(f_io_names(&cmd[i + 2], 1), APPEND_MODE));
		i++;
	}
	return (-1);
}
