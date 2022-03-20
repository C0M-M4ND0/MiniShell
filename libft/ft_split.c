/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:46:07 by eabdelha          #+#    #+#             */
/*   Updated: 2022/03/15 11:36:59 by eabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*ft_free(char **ss)
{
	int	i;

	i = -1;
	while (ss[++i])
		free(ss[i]);
	free(ss);
	return (NULL);
}

static void	ft_fil_ss(char const *s, char *ss, int fi, int li)
{
	int	j;

	j = 0;
	while (fi < li)
		ss[j++] = s[fi++];
	ss[j] = '\0';
}

static void	get_len_word(char const *s, int *i, char c)
{
	int	hol;

	while (s[*i] != c && s[*i] != '\0')
	{
		hol = check_quotes((char *)&s[*i]);
		if (hol > 0 && s[hol + (*i)])
			(*i) += hol;
		(*i)++;
	}
}

static	int	ft_switch(char const *s, char **ss, int aut, char c)
{
	int	i;
	int	j;
	int	fi;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		fi = i;
		get_len_word(s, &i, c);
		if (aut < 0 && fi != i)
		{
			ss[++j] = (char *)malloc(sizeof(char) * (i - fi + 1));
			if (ss[j] == NULL)
				return (-2);
			ft_fil_ss(s, ss[j], fi, i);
		}
		if (aut >= 0 && fi != i)
			aut++;
	}
	return (aut);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;
	int		cmp;

	cmp = 0;
	ss = NULL;
	if (!s)
		return (0);
	cmp = ft_switch(s, ss, 0, c);
	ss = (char **)malloc(sizeof(char *) * (cmp + 1));
	if (ss == NULL)
		return (NULL);
	ss[cmp] = NULL;
	cmp = ft_switch(s, ss, -1, c);
	if (cmp == -2)
		ft_free(ss);
	return (ss);
}
