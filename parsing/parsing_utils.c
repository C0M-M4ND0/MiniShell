/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:10:48 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/18 16:10:49 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	to_space(char *str, size_t start, size_t len)
{
	if (!str)
		return ;
	if (start >= ft_strlen(str))
		len = 0;
	if (len > ft_strlen(&str[start]))
		len = ft_strlen(&str[start]);
	while (len-- > 0)
	{
		str[start] = ' ';
		start++;
	}
}

void	remove_quotes_1d(char *str)
{
	int	j;
	int	hol;
	int	hhol;

	j = 0;
	while (str[j])
	{
		hol = check_quotes(&str[j]);
		hhol = hol + j - 2;
		if (hol > 0 && str[j + hol])
		{
			while (str[j + hol])
			{
				str[j + hol] = str[j + hol + 1];
				hol++;
			}
			while (str[j])
			{
				str[j] = str[j + 1];
				j++;
			}
			j = hhol;
		}
		j++;
	}
}

void	remove_quotes_2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		remove_quotes_1d(strs[i]);
		i++;
	}
}
