/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grt_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 05:25:11 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/18 10:47:24 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i])
		i++;
	return (i);
}

int	ft_strchr2(char *s)
{
	int	i;

	i = 0;
	while (s != NULL && s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin2(char *s1, char *s2, int rt)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	s2[rt] = '\0';
	if (s1 != NULL)
		j = ft_strlen2(s1);
	s = (char *)malloc((size_t)(j + ft_strlen2(s2) + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	if (s1 != NULL)
		free(s1);
	return (s);
}
