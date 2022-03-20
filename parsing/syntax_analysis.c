/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:11:03 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:11:05 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	consecutive_pipe(char *str)
{
	int	i;
	int	cmp_pipe;

	i = 0;
	while (str && str[i])
	{
		cmp_pipe = 0;
		while (str[i] == '>' || str[i] == '<'
			|| str[i] == '|' || str[i] == ' ' || str[i] == '&')
		{
			if (str[i] == '|' || str[i] == '&' || ((str[i] == '>'
						|| str[i] == '<') && !cmp_pipe))
				cmp_pipe++;
			i++;
		}
		if (cmp_pipe > 1)
			return (0);
		i += check_quotes(&str[i]) + 1;
		i += check_parenthesis(&str[i]);
	}
	return (1);
}

int	check_genral_syntax(char *str)
{
	str = ft_strtrim(str, " ");
	if (!str[0])
		return (free(str), 2);
	if (str[0] == '|' || !consecutive_pipe(str))
		return (free(str), 0);
	if (str[ft_strlen(str) - 1] == '<'
		|| str[ft_strlen(str) - 1] == '>')
		return (free(str), -1);
	if (str[0] == '&' || str[ft_strlen(str) - 1] == '&')
		return (free(str), 3);
	if (str[ft_strlen(str) - 1] == '|'
		|| str[ft_strlen(str) - 1] == '\\')
		return (free(str), -2);
	return (free(str), 1);
}

int	consecutive_redir_symbol(char *str)
{
	int	i;
	int	cmp_redir;

	i = 0;
	while (str[i])
	{
		cmp_redir = 0;
		while (str[i] == '<' || str[i] == '>' || str[i] == ' ')
		{
			if (str[i] == '<' || str[i] == '>')
				cmp_redir++;
			i++;
		}
		if (cmp_redir > 2)
			return (0);
		i += check_quotes(&str[i]) + 1;
	}
	return (1);
}

int	contradict_redir_symbol(char *str, char symbol_one, char symbol_two)
{
	int	i;
	int	cmp_redir;

	i = 0;
	while (str[i])
	{
		cmp_redir = 0;
		while (str[i] == symbol_one || str[i] == ' ')
		{
			if (str[i] == symbol_one)
				cmp_redir++;
			i++;
		}
		if (str[i] == symbol_two && cmp_redir)
			return (0);
		i += check_quotes(&str[i]) + 1;
	}
	return (1);
}

int	check_redirection_syntax(char *str)
{
	if (!consecutive_redir_symbol(str))
		return (0);
	if (!contradict_redir_symbol(str, '<', '>'))
		return (0);
	if (!contradict_redir_symbol(str, '>', '<'))
		return (0);
	return (1);
}
