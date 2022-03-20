/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 08:28:33 by eabdelha          #+#    #+#             */
/*   Updated: 2021/11/08 09:06:08 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_first_i(char const *s, char const *set)
{
	int	i;
	int	j;
	int	ch;

	i = 0;
	while (s[i])
	{
		ch = 0;
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				ch = 1;
			j++;
		}
		if (ch == 0)
			return (i);
		i++;
	}
	return (0);
}

static int	get_last_i(char const *s, char const *set)
{
	int	i;
	int	j;
	int	ch;

	i = (ft_strlen(s) - 1);
	while (i >= 0)
	{
		ch = 0;
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				ch = 1;
			j++;
		}
		if (ch == 0)
			return (i + 1);
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		fi;
	int		li;
	int		j;

	if (!s1 || !set)
		return (NULL);
	fi = get_first_i(s1, set);
	li = get_last_i(s1, set);
	s2 = (char *)malloc((size_t)(li - fi + 1));
	if (s2 == NULL)
		return (NULL);
	j = 0;
	while (fi < li && li != 0)
		s2[j++] = s1[fi++];
	s2[j] = '\0';
	return (s2);
}
