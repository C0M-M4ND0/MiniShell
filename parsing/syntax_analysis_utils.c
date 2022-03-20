/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:10:56 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:10:57 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unclosed_quote(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		i += check_quotes(&line[i]) + 1;
		if (!line[i - 1])
			return (1);
	}
	return (0);
}

int	unclosed_parenthesis(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		i += check_quotes(&line[i]);
		i += check_parenthesis(&line[i]);
		if (!line[i++])
			return (1);
		if (line[i] == ')')
			return (1);
	}
	return (0);
}

int	check_valid_parenthesis(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '(')
		i++;
	while (line[i])
	{
		if (line[i] == '(')
			return (1);
		i++;
	}
	i = 0;
	while (line[i] && line[i] != ')')
		i++;
	while (line[i] && (line[i] == ')' || line[i] == ' '))
		i++;
	if (line[i])
		return (1);
	return (0);
}

int	check_special_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i += check_quotes(&line[i]);
		if (line[i] == ';' || line[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}
