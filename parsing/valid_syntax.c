/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:11:12 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:11:14 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_conditions(char *line)
{
	int	check_ret;

	check_ret = check_genral_syntax(line);
	if (check_ret == 2)
		return (ft_putendl_fd(ERR_LOGIC, STDERR_FILENO), 0);
	else if (check_ret == -1)
		return (ft_putendl_fd(LINE_TOKEN, STDERR_FILENO), 0);
	else if (check_ret == -2)
		return (ft_putendl_fd(MULTI_LINE, STDERR_FILENO), 0);
	else if (!check_ret)
		return (ft_putendl_fd(PIPE_TOKEN, STDERR_FILENO), 0);
	else if (check_ret == 3)
		return (ft_putendl_fd(AND_TOKEN, STDERR_FILENO), 0);
	else if (!check_redirection_syntax(line))
		return (ft_putendl_fd(REDIR_TOKEN, STDERR_FILENO), 0);
	else if (check_valid_parenthesis(line))
		return (ft_putendl_fd(PARENTH_TOKEN, STDERR_FILENO), 0);
	return (1);
}

int	logic_syntax(char *line, t_list **l_cmd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i += check_quotes(&line[i]);
		if (line[i++] == '\0')
			return (-1);
		if ((line[i] == '|' && line[i + 1] == '|')
			|| (line[i] == '&' && line[i + 1] == '&'))
		{
			line[i++] = '\0';
			line[i] = ' ';
			ft_lstadd_back(l_cmd, ft_lstnew(&(line[i])));
		}
	}
	return (0);
}

int	valid_syntax(char *line)
{
	int		i;
	t_list	*l_cmd;
	t_list	*l_hol;

	i = 0;
	if (unclosed_quote(line))
		return (ft_putendl_fd(ERR_QUOTES, STDERR_FILENO), 0);
	if (unclosed_parenthesis(line))
		return (ft_putendl_fd(ERR_PARENTH, STDERR_FILENO), 0);
	if (check_special_char(line))
		return (ft_putendl_fd(ERR_S_CHAR, STDERR_FILENO), 0);
	line = ft_strdup(line);
	l_cmd = ft_lstnew(&line[0]);
	l_hol = l_cmd;
	logic_syntax(line, &l_cmd);
	while (l_cmd)
	{
		if (!syntax_conditions((char *)l_cmd->content))
			return (ft_lstclear(&l_hol, NULL), free(line), 0);
		l_cmd = l_cmd->next;
	}
	free(line);
	ft_lstclear(&l_hol, NULL);
	return (1);
}
