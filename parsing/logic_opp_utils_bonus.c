/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_opp_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:09:56 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:09:57 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parenthesis(char *cmd)
{
	int	i;

	i = 0;
	if (cmd && cmd[i] && cmd[i] == '(')
	{
		i++;
		while (cmd && cmd[i] && cmd[i] != ')')
		{
			if (cmd[i] == '(')
				i += check_parenthesis(&cmd[i]);
			i++;
		}
	}
	return (i);
}

int	check_priorities(char *cmd)
{
	int	i;
	int	f_i;
	int	l_i;

	i = 0;
	while (cmd && cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd && cmd[i] == '(')
	{
		f_i = i;
		i = check_parenthesis(&cmd[i]) + i + 1;
		l_i = i - 1;
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (!cmd[i])
		{
			cmd[l_i] = ' ';
			cmd[f_i] = ' ';
			return (1);
		}
	}
	return (0);
}

char	*get_last_cmd(char *cmd, int *logic_opp)
{
	int	i;
	int	pos_and;
	int	pos_or;

	i = 0;
	pos_and = -1;
	pos_or = -1;
	while (cmd[i])
	{
		i += check_parenthesis(&cmd[i]);
		i += check_quotes(&cmd[i]);
		if (cmd[i++] == '\0')
			return (NULL);
		if (cmd[i] == '|' && cmd[i + 1] == '|')
			pos_or = i;
		if (cmd[i] == '&' && cmd[i + 1] == '&')
			pos_and = i;
	}
	if (pos_or > pos_and && ++(*logic_opp) != 0)
		return (cmd[pos_or] = '\0', cmd[pos_or + 1] = ' ', &cmd[pos_or + 1]);
	else if (pos_or < pos_and && --(*logic_opp) != 0)
		return (cmd[pos_and] = '\0', cmd[pos_and + 1] = ' ', &cmd[pos_and + 1]);
	return (NULL);
}
